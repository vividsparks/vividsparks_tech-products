//
// this is an example of "host code" that can either run in cosim or on the PS
// we can use the same C host code and
// the API we provide abstracts away the
// communication plumbing differences.

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <pthread.h>
#include <time.h>
#include <queue>
#include <unistd.h>
#include <bitset>

#include "ps.hpp"

#include "RacEr_zynq_pl.h"
#include "RacEr_printing.h"
#include "RacEr_tag_bitbang.h"
#include "RacEr_argparse.h"

#include "RacEr_manycore_machine.h"
#include "RacEr_manycore_packet.h"

#ifndef DRAM_ALLOCATE_SIZE_MB
#define DRAM_ALLOCATE_SIZE_MB 128
#endif
#define DRAM_ALLOCATE_SIZE (DRAM_ALLOCATE_SIZE_MB * 1024 * 1024)

#ifndef ZYNQ_PL_DEBUG
#define ZYNQ_PL_DEBUG 0
#endif

void nbf_load(RacEr_zynq_pl *zpl, char *filename);

inline void send_mc_request_packet(RacEr_zynq_pl *zpl, hb_mc_request_packet_t *packet) {
  int axil_len = sizeof(hb_mc_request_packet_t) / 4;

  uint32_t *pkt_data = reinterpret_cast<uint32_t *>(packet);
  for (int i = 0; i < axil_len; i++) {
    while (!zpl->shell_read(GP0_RD_EP_REQ_FIFO_CTR));
    zpl->shell_write(GP0_WR_EP_REQ_FIFO_DATA, pkt_data[i], 0xf);
  }
}

inline void recv_mc_response_packet(RacEr_zynq_pl *zpl, hb_mc_response_packet_t *packet) {
  int axil_len = sizeof(hb_mc_response_packet_t) / 4;

  uint32_t *pkt_data = reinterpret_cast<uint32_t *>(packet);
  for (int i = 0; i < axil_len; i++) {
    while (!zpl->shell_read(GP0_RD_MC_RSP_FIFO_CTR));
    pkt_data[i] = zpl->shell_read(GP0_RD_MC_RSP_FIFO_DATA);
  }
}

inline void recv_mc_request_packet(RacEr_zynq_pl *zpl, hb_mc_request_packet_t *packet) {
  int axil_len = sizeof(hb_mc_request_packet_t) / 4;

  uint32_t *pkt_data = reinterpret_cast<uint32_t *>(packet);
  for (int i = 0; i < axil_len; i++) {
    while (!zpl->shell_read(GP0_RD_MC_REQ_FIFO_CTR));
    pkt_data[i] = zpl->shell_read(GP0_RD_MC_REQ_FIFO_DATA);
  }
}

inline void send_mc_write(RacEr_zynq_pl *zpl, uint8_t x, uint8_t y, uint32_t epa, int32_t data) {
  RacEr_pr_dbg_ps("Writing: (%x %x) [%x]<-%x\n", x, y, epa, data);
  hb_mc_request_packet_t req_pkt;

  req_pkt.op_v2   = 2; // SW
  req_pkt.reg_id  = 0xff; // unused
  req_pkt.payload = data;
  req_pkt.x_src   = RACER_MANYCORE_MACHINE_HOST_COORD_X;
  req_pkt.y_src   = RACER_MANYCORE_MACHINE_HOST_COORD_Y;
  req_pkt.x_dst   = x;
  req_pkt.y_dst   = y;
  req_pkt.addr    = epa >> 2;

  send_mc_request_packet(zpl, &req_pkt);
}

inline int32_t send_mc_read(RacEr_zynq_pl *zpl, uint8_t x, uint8_t y, uint32_t epa) {
  hb_mc_request_packet_t req_pkt;

  req_pkt.op_v2   = 0; // LD
  req_pkt.reg_id  = 0xff; // unused
  req_pkt.payload = 0; // Ignore payload
  req_pkt.x_src   = RACER_MANYCORE_MACHINE_HOST_COORD_X;
  req_pkt.y_src   = RACER_MANYCORE_MACHINE_HOST_COORD_Y;
  req_pkt.x_dst   = x;
  req_pkt.y_dst   = y;
  req_pkt.addr    = epa >> 2;

  send_mc_request_packet(zpl, &req_pkt);

  hb_mc_response_packet_t resp_pkt;
  recv_mc_response_packet(zpl, &resp_pkt);
  RacEr_pr_dbg_ps("Querying: [%x] == %x\n", epa, resp_pkt.data);

  return resp_pkt.data;
}

int ps_main(int argc, char **argv) {
  RacEr_zynq_pl *zpl = new RacEr_zynq_pl(argc, argv);

  RacEr_pr_info("ps.cpp: reading three base registers\n");
  RacEr_pr_info("ps.cpp: dram_base=%lx\n", zpl->shell_read(0x00 + gp0_addr_base));

  uint32_t val;
  zpl->shell_write(GP0_WR_CSR_DRAM_BASE, 0xDEADBEEF, 0xf);
  assert((zpl->shell_read(GP0_RD_CSR_DRAM_BASE) == (0xDEADBEEF)));
  zpl->shell_write(GP0_WR_CSR_DRAM_BASE, val, 0xf);
  assert((zpl->shell_read(GP0_RD_CSR_DRAM_BASE) == val));

  RacEr_tag_bitbang *btb = new RacEr_tag_bitbang(zpl, GP0_WR_CSR_TAG_BITBANG, TAG_NUM_CLIENTS, TAG_MAX_LEN);
  RacEr_tag_client *mc_reset_client = new RacEr_tag_client(TAG_CLIENT_MC_RESET_ID, TAG_CLIENT_MC_RESET_WIDTH);

  // Reset the RacEr tag master
  btb->reset_master();
  // Reset RacEr client0
  btb->reset_client(mc_reset_client);
  // Set RacEr client0 to 1 (assert HK reset)
  btb->set_client(mc_reset_client, 0x1);
  // Set RacEr client0 to 0 (deassert HK reset)
  btb->set_client(mc_reset_client, 0x0);

  // We need some additional toggles for data to propagate through
  btb->idle(50);
  // Deassert the active-low system reset as we finish initializing the whole system
  zpl->shell_write(GP0_WR_CSR_SYS_RESETN, 0x1, 0xF);

  unsigned long phys_ptr;
  volatile int32_t *buf;
  int i;
  long allocated_dram = DRAM_ALLOCATE_SIZE;
  RacEr_pr_info("ps.cpp: calling allocate dram with size %ld\n", allocated_dram);
  buf = (volatile int32_t *)zpl->allocate_dram(allocated_dram, &phys_ptr);
   for (i = 0; i < allocated_dram/ 4; i++)
        buf[i] = 0xDEEDCEEF;
  RacEr_pr_info("ps.cpp: received %p (phys = %lx)\n", buf, phys_ptr);
  zpl->shell_write(GP0_WR_CSR_DRAM_BASE, phys_ptr, 0xf);
  assert((zpl->shell_read(GP0_RD_CSR_DRAM_BASE) == (int32_t)phys_ptr));
  RacEr_pr_info("ps.cpp: wrote and verified base register\n");

  if (argc == 1) {
    RacEr_pr_warn(
        "No nbf file specified, sleeping for 2^31 seconds (this will hold "
        "onto allocated DRAM)\n");
    sleep(1U << 31);
    delete zpl;
    return -1;
  }

  nbf_load(zpl, argv[1]);

  int finished = 0;
  while (finished != NUM_FINISH) {
    RacEr_pr_dbg_ps("Waiting for incoming request packet\n");
    hb_mc_request_packet_t mc_pkt;
    recv_mc_request_packet(zpl, &mc_pkt);
    RacEr_pr_dbg_ps("Request packet signaled\n");
    int mc_epa = (mc_pkt.addr << 2) & 0xffff; // Trim to 16b EPA
    int mc_data = mc_pkt.payload;
    RacEr_pr_dbg_ps("Request packet [%x] = %x\n", mc_epa, mc_data);
    if (mc_epa == 0xeadc || mc_epa == 0xeee0) {
        printf("%c", mc_data & 0xff);
        fflush(stdout);
    } else if (mc_epa == 0xead0) {
      RacEr_pr_info("Finish packet received %d\n", ++finished);
    } else {
      RacEr_pr_info("Errant request packet: %x %x\n", mc_epa, mc_data);
    }
  }

  zpl->done();
  delete zpl;
  return 0;
}

void nbf_load(RacEr_zynq_pl *zpl, char *nbf_filename) {
  string nbf_command;
  string tmp;
  string delimiter = "_";

  long long int nbf[4];
  int pos = 0;
  long unsigned int base_addr;
  int data;
  ifstream nbf_file(nbf_filename);

  if (!nbf_file.is_open()) {
    RacEr_pr_err("ps.cpp: error opening nbf file.\n");
    delete zpl;
    return;
  }

  int line_count = 0;
  while (getline(nbf_file, nbf_command)) {
    line_count++;
    int i = 0;
    while ((pos = nbf_command.find(delimiter)) != std::string::npos) {
      tmp = nbf_command.substr(0, pos);
      nbf[i] = std::stoull(tmp, nullptr, 16);
      nbf_command.erase(0, pos + 1);
      i++;
    }
    nbf[i] = std::stoull(nbf_command, nullptr, 16);

    int x_tile   = nbf[0];
    int y_tile   = nbf[1];
    int epa      = nbf[2]; // word addr
    int nbf_data = nbf[3];

    bool finish = (x_tile == 0xff) && (y_tile == 0xff) && (epa == 0x00000000) && (nbf_data == 0x00000000);
    bool fence  = (x_tile == 0xff) && (y_tile == 0xff) && (epa == 0xffffffff) && (nbf_data == 0xffffffff);

    if (finish) {
      RacEr_pr_dbg_ps("ps.cpp: nbf finish command, line %d\n", line_count);
      continue;
    } else if (fence) {
      RacEr_pr_dbg_ps("ps.cpp: nbf fence command (ignoring), line %d\n", line_count);
      RacEr_pr_info("Waiting for credit drain\n");
      while(zpl->shell_read(GP0_RD_CREDIT_COUNT) > 0);
      RacEr_pr_info("Credits drained\n");
      continue;
    } else {
      send_mc_write(zpl, x_tile, y_tile, epa << 2, nbf_data);

#ifdef VERIFY_NBF

      int32_t verif_data;
     
      verif_data = send_mc_read(zpl, x_tile, y_tile, epa << 2);

      // Some verification reads are expected to fail e.g. CSRs
      if (req_pkt.payload == resp_pkt.data) {
        RacEr_pr_info("Received verification: %x==%x\n", req_pkt.payload, resp_pkt.data);
      } else {
        RacEr_pr_info("Failed verification: %x!=%x\n", req_pkt.payload, resp_pkt.data);
      }
#endif
    }
  }
}

