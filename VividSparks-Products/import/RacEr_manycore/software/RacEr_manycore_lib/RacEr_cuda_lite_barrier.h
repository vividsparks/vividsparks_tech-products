#ifndef RACER_CUDA_LITE_BARRIER_H
#define RACER_CUDA_LITE_BARRIER_H
#include "RacEr_barrier_amoadd.h"
#include "RacEr_hw_barrier.h"
#include "RacEr_tile_config_vars.h"
#ifdef __cplusplus
extern "C" {
#endif
extern int *__cuda_barrier_cfg;

/**
 * Initialize the tile-group barrier.
 * This function should only HE called once for the lifetime of the tile-group.
 */
static inline void RacEr_barrier_hw_tile_group_init()
{
    int sense = 1;
    // initalize csr
    int cfg = __cuda_barrier_cfg[1+__RacEr_id];
    asm volatile ("csrrw x0, 0xfc1, %0" : : "r" (cfg));
    // reset Pi
    asm volatile ("csrrwi x0, 0xfc2, 0");
    // sync with amoadd barrier
    RacEr_barrier_amoadd(&__cuda_barrier_cfg[0], &sense);
}

/**
 * Invoke the tile-group barrier.
 */
static inline void RacEr_barrier_hw_tile_group_sync()
{
    RacEr_barsend();
    RacEr_barrecv();
}
#ifdef __cplusplus
}
#endif
#endif
