// Copyright (c) 2020, VividSparks IT Solutions Pvt. Ltd.  All rights reserved.
//
// Redistribution and use in source and binary forms, modifications,
// are NOT permitted.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
// ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef RACER_MANYCORE_FIFO_H
#define RACER_MANYCORE_FIFO_H

#include <RacEr_manycore_features.h>
#include <RacEr_manycore_packet.h>

#ifdef __cplusplus
extern "C" {
#endif

        /* hb_mc_fifo_rx_t identifies the type of a packet receive operation*/
        typedef enum __hb_mc_direction_t {  /*  */
                HB_MC_MMIO_FIFO_MIN       = 0,
                HB_MC_MMIO_FIFO_TO_DEVICE = 0,
                HB_MC_MMIO_FIFO_TO_HOST   = 1,
                HB_MC_MMIO_FIFO_MAX       = 1
        } hb_mc_direction_t;

        static inline const char *hb_mc_direction_to_string(hb_mc_direction_t dir)
        {
                static const char *strtab [] = {
                        [HB_MC_MMIO_FIFO_TO_DEVICE] = "host-initiated",
                        [HB_MC_MMIO_FIFO_TO_HOST]   = "device-initiated",
                };

                return strtab[dir];
        }

        /*
         * hb_mc_fifo_rx_t identifies the type of a packet receive operation. MIN & MAX
         * are not fifo directions, they are used for iteration over fifos.
         */
        typedef enum __hb_mc_fifo_rx_t {
                HB_MC_FIFO_RX_RSP = HB_MC_MMIO_FIFO_TO_DEVICE,
                HB_MC_FIFO_RX_REQ = HB_MC_MMIO_FIFO_TO_HOST
        } hb_mc_fifo_rx_t;

        static inline const char *hb_mc_fifo_rx_to_string(hb_mc_fifo_rx_t type)
        {
                static const char *strtab [] = {
                        [HB_MC_FIFO_RX_RSP] = "rx-responses",
                        [HB_MC_FIFO_RX_REQ] = "rx-requests",
                };

                return strtab[type];
        }

        /*
         * hb_mc_fifo_tx_t identifies the type of a packet transmit operation. MIN & MAX
         * are not fifo directions, they are used for iteration over fifos.
         */
        typedef enum __hb_mc_fifo_tx_t {  /*  */
                HB_MC_FIFO_TX_REQ = HB_MC_MMIO_FIFO_TO_DEVICE,
                HB_MC_FIFO_TX_RSP = HB_MC_MMIO_FIFO_TO_HOST
        } hb_mc_fifo_tx_t;

        static inline const char *hb_mc_fifo_tx_to_string(hb_mc_fifo_tx_t type)
        {
                static const char *strtab [] = {
                        [HB_MC_FIFO_TX_REQ] = "tx-requests",
                        [HB_MC_FIFO_TX_RSP] = "tx-responses",
                };
                return strtab[type];
        }

        inline hb_mc_direction_t hb_mc_get_rx_direction(hb_mc_fifo_rx_t d){
                return (hb_mc_direction_t)d;
        }

        inline hb_mc_direction_t hb_mc_get_tx_direction(hb_mc_fifo_tx_t d){
                return (hb_mc_direction_t)d;
        }


#ifdef __cplusplus
}
#endif
#endif
