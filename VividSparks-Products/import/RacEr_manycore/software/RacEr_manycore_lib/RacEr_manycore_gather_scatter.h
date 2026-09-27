/**
 *    RacEr_manycore_gather_scatter.h
 *
 *
 */


#include "RacEr_manycore.h"
#include "RacEr_mutex.h"

#define GS_CSR_OFFSET       0x20000
#define GS_RUN_ADDR         ((0<<2) | GS_CSR_OFFSET)
#define GS_ACCESS_LEN_ADDR  ((1<<2) | GS_CSR_OFFSET)
#define GS_STRIDE_ADDR      ((2<<2) | GS_CSR_OFFSET)
#define GS_EVA_BASE_ADDR    ((3<<2) | GS_CSR_OFFSET)

// Lock gather-scatter.
// x: x-cordinate of gather-scatter.
// y: y-cordinate of gather-scatter.
void RacEr_manycore_gs_lock(int x, int y)
{
  RacEr_mutex_ptr gs_lock = RacEr_remote_ptr(x,y,0);
  RacEr_mutex_lock(gs_lock);
}

// Unlock gather-scatter.
// x: x-cordinate of gather-scatter.
// y: y-cordinate of gather-scatter.
void RacEr_manycore_gs_unlock(int x, int y)
{
  RacEr_mutex_ptr gs_lock = RacEr_remote_ptr(x,y,0);
  RacEr_mutex_unlock(gs_lock);
}

// helper function
// x: x-cordinate of gather-scatter.
// y: y-cordinate of gather-scatter.
// eva_base: EVA base address of gather/scatter op.
// stride: Access stride in unit of words
// access_len: number of words accessed per gather/scatter op.
// scatter_not_gather: 1=scatter, 0=gather. 
void RacEr_manycore_gs_helper(int x, int y, int* eva_base, int stride,
  int access_len, int* reserve_addr, int scatter_not_gather)
{
  // set access len
  RacEr_global_store(x, y, GS_ACCESS_LEN_ADDR, access_len);

  // set stride
  RacEr_global_store(x, y, GS_STRIDE_ADDR, stride);

  // set EVA base
  RacEr_global_store(x, y, GS_EVA_BASE_ADDR, eva_base);

  // hit run button
  RacEr_global_store(x, y, GS_RUN_ADDR, (scatter_not_gather<<31) | (int) reserve_addr);

  // go to sleep.
  *reserve_addr = 0;
  RacEr_wait_local_int(reserve_addr, 1);
}

// Gather
void RacEr_manycore_gs_gather(int x, int y, int* eva_base, int stride, int access_len, int* reserve_addr)
{
  RacEr_manycore_gs_helper(x,y,eva_base,stride,access_len,reserve_addr,0);
}

// Scatter
void RacEr_manycore_gs_scatter(int x, int y, int* eva_base, int stride, int access_len, int* reserve_addr)
{
  RacEr_manycore_gs_helper(x,y,eva_base,stride,access_len,reserve_addr,1);
}


