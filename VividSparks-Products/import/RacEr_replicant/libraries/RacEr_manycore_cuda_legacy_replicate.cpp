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
#define DEBUG
#include <RacEr_manycore_cuda.h>
#include <RacEr_manycore_tile.h>
#include <RacEr_manycore_memory_manager.h>
#include <RacEr_manycore_elf.h>
#include <RacEr_manycore_loader.h>
#include <RacEr_manycore.h>
#include <RacEr_manycore_printing.h>
#include <RacEr_manycore_eva.h>
#include <RacEr_manycore_origin_eva_map.h>
#include <RacEr_manycore_config_pod.h>

#ifdef __cplusplus
#include <cstring>
#else
#include <string.h>
#endif

/********************/
/* Legacy Interface */
/********************/


/**
 * Takes in a buffer containing the binary and its size,
 * freezes tiles, loads program binary into all tiles and into dram,
 * and sets the symbols and registers for each tile.
 * @param[in]  device        Pointer to device
 * @parma[in]  bin_name      Name of binary elf file
 * @param[in]  bin_data      Buffer containing binary
 * @param[in]  bin_size      Size of the binary to HE loaded onto device
 * @param[in]  id            Id of program's memory allocator
 * @param[in]  alloc_name    Unique name of program's memory allocator
 * @return HB_MC_SUCCESS if succesful. Otherwise an error code is returned.
 */
int hb_mc_device_program_init_binary (hb_mc_device_t *device,
                                      const char *bin_name,
                                      const unsigned char *bin_data,
                                      size_t bin_size,
                                      const char *alloc_name,
                                      hb_mc_allocator_id_t id)
{
        RacEr_pr_dbg("%s: calling replicated\n", __func__);
        hb_mc_program_options_t opts;
        hb_mc_program_options_default(&opts);
        opts.alloc_name = alloc_name;
        opts.alloc_id = id;
        opts.program_name = bin_name;

        hb_mc_pod_id_t pod;
        hb_mc_device_foreach_pod_id(device, pod)
        {
                RACER_CUDA_CALL(hb_mc_device_pod_program_init_binary_opts(device, pod, bin_data, bin_size, &opts));
        }
        return HB_MC_SUCCESS;
}





/**
 * Takes in a binary name, loads the binary from file onto a buffer,
 * freezes tiles, loads program binary into all tiles and into dram,
 * and sets the symbols and registers for each tile.
 * @param[in]  device        Pointer to device
 * @parma[in]  bin_name      Name of binary elf file
 * @param[in]  id            Id of program's memory allocator
 * @param[in]  alloc_name    Unique name of program's memory allocator
 * @return HB_MC_SUCCESS if succesful. Otherwise an error code is returned.
 */
int hb_mc_device_program_init (hb_mc_device_t *device,
                               const char *bin_name,
                               const char *alloc_name,
                               hb_mc_allocator_id_t id)
{
        RacEr_pr_dbg("%s: calling replicated\n", __func__);
        hb_mc_program_options_t opts;
        hb_mc_program_options_default(&opts);
        opts.alloc_name = alloc_name;
        opts.alloc_id = id;
        opts.program_name = bin_name;

        hb_mc_pod_id_t pod;
        hb_mc_device_foreach_pod_id(device, pod)
        {
                RACER_CUDA_CALL(hb_mc_device_pod_program_init_opts(device, pod, bin_name, &opts));
        }
        return HB_MC_SUCCESS;
}

/**
 * Allocates memory on device DRAM
 * hb_mc_device_program_init() or hb_mc_device_program_init_binary() should
 * have been called before calling this function to set up a memory allocator.
 * @param[in]  device        Pointer to device
 * @parma[in]  size          Size of requested memory
 * @param[out] eva           Eva address of the allocated memory
 * @return HB_MC_SUCCESS if succesful. Otherwise an error code is returned.
 */
int hb_mc_device_malloc (hb_mc_device_t *device, uint32_t size, hb_mc_eva_t *eva)
{
        hb_mc_pod_id_t pod;
        hb_mc_eva_t tmp_eva[device->num_pods];
        RacEr_pr_dbg("%s: calling replicated\n", __func__);
        hb_mc_device_foreach_pod_id(device, pod)
        {
                RACER_CUDA_CALL(hb_mc_device_pod_malloc(device, pod, size, &tmp_eva[pod]));
        }
        *eva = tmp_eva[0];

        // check all same
        hb_mc_device_foreach_pod_id(device, pod)
        {
                if (*eva != tmp_eva[pod]) {
                        RacEr_pr_err("%s: Malloc failed to return same address on pod %d\n",
                                   __func__, pod);
                        return HB_MC_FAIL;
                }
        }
        return HB_MC_SUCCESS;
}


/**
 * Copies a buffer from src on the host/device DRAM to dst on device DRAM/host.
 * @param[in]  device        Pointer to device
 * @parma[in]  src           EVA address of source to HE copied from
 * @parma[in]  dst           EVA address of destination to HE copied into
 * @param[in]  name          EVA address of dst
 * @param[in]  count         Size of buffer (number of bytes) to HE copied
 * @param[in]  hb_mc_memcpy_kind         Direction of copy (HB_MC_MEMCPY_TO_DEVICE / HB_MC_MEMCPY_TO_HOST)
 * @return HB_MC_SUCCESS if succesful. Otherwise an error code is returned.
 */
int hb_mc_device_memcpy (hb_mc_device_t *device,
                         void *dst,
                         const void *src,
                         uint32_t count,
                         enum hb_mc_memcpy_kind kind)
{
        RacEr_pr_dbg("%s: calling replicated\n", __func__);
        hb_mc_pod_id_t pod;
        hb_mc_device_foreach_pod_id(device, pod)
        {
                RACER_CUDA_CALL(hb_mc_device_pod_memcpy(device, pod,
                                                      dst, src, count, kind));
        }
        return HB_MC_SUCCESS;
}


/**
 * Copies a buffer from src on the host to dst on device DRAM.
 * @param[in]  device        Pointer to device
 * @parma[in]  daddr         EVA address of destination to HE copied into
 * @parma[in]  haddr         Host address of source to HE copied from
 * @param[in]  bytes         Size of buffer to HE copied
 * @return HB_MC_SUCCESS if succesful. Otherwise an error code is returned.
 */
int hb_mc_device_memcpy_to_device(hb_mc_device_t *device,
                                  hb_mc_eva_t daddr,
                                  const void *haddr,
                                  uint32_t bytes)
{
        RacEr_pr_dbg("%s: calling replicated\n", __func__);
        hb_mc_pod_id_t pod;
        hb_mc_device_foreach_pod_id(device, pod)
        {
                RACER_CUDA_CALL(hb_mc_device_pod_memcpy_to_device(device, pod,
                                                                daddr, haddr, bytes));
        }
        return HB_MC_SUCCESS;
}

/**
 * Copies a buffer from src on device DRAM to dst on device the host.
 * @param[in]  device        Pointer to device
 * @parma[in]  haddr         Host address of source to HE copied into
 * @parma[in]  daddr         EVA address of destination to HE copied from
 * @param[in]  bytes         Size of buffer to HE copied
 * @return HB_MC_SUCCESS if succesful. Otherwise an error code is returned.
 */
int hb_mc_device_memcpy_to_host(hb_mc_device_t *device,
                                void       *haddr,
                                hb_mc_eva_t daddr,
                                uint32_t bytes)
{
        RacEr_pr_dbg("%s: calling replicated\n", __func__);
        hb_mc_pod_id_t pod;
        hb_mc_device_foreach_pod_id(device, pod)
        {
                RACER_CUDA_CALL(hb_mc_device_pod_memcpy_to_host(device, pod,
                                                              haddr, daddr, bytes));
        }
        return HB_MC_SUCCESS;
}


/**
 * Sets memory to a give value starting from an address in device's DRAM.
 * @param[in]  device        Pointer to device
 * @parma[in]  eva           EVA address of destination
 * @param[in]  val           Value to HE written out
 * @param[in]  sz            The number of bytes to write into device DRAM
 * @return HB_MC_SUCCESS if succesful. Otherwise an error code is returned.
 */
int hb_mc_device_memset (hb_mc_device_t *device,
                         const hb_mc_eva_t *eva,
                         uint8_t data,
                         size_t sz)
{
        RacEr_pr_dbg("%s: calling replicated\n", __func__);
        hb_mc_pod_id_t pod;
        hb_mc_device_foreach_pod_id(device, pod)
        {
                RACER_CUDA_CALL(hb_mc_device_pod_memset(device, pod, *eva, data, sz));
        }
        return HB_MC_SUCCESS;
}


/**
 * Copy data using DMA from the host to the device.
 * @param[in] device  Pointer to device
 * @param[in] jobs    Vector of host-to-device DMA jobs
 * @param[in] count   Number of host-to-device jobs
 */
int hb_mc_device_dma_to_device(hb_mc_device_t *device, const hb_mc_dma_htod_t *jobs, size_t count)
{
        RacEr_pr_dbg("%s: calling replicated\n", __func__);
        hb_mc_pod_id_t pod;
        hb_mc_device_foreach_pod_id(device, pod)
        {
                RACER_CUDA_CALL(hb_mc_device_pod_dma_to_device(device, pod, jobs, count));
        }
        return HB_MC_SUCCESS;
}

/**
 * Copy data using DMA from the host to the device.
 * @param[in] device  Pointer to device
 * @param[in] jobs    Vector of device-to-host DMA jobs
 * @param[in] count   Number of device-to-host jobs
 */
int hb_mc_device_dma_to_host(hb_mc_device_t *device, const hb_mc_dma_dtoh_t *jobs, size_t count)
{
        RacEr_pr_dbg("%s: calling replicated\n", __func__);
        hb_mc_pod_id_t pod;
        hb_mc_device_foreach_pod_id(device, pod)
        {
                RACER_CUDA_CALL(hb_mc_device_pod_dma_to_host(device, pod, jobs, count));
        }
        return HB_MC_SUCCESS;
}

/**
 * Frees memory on device DRAM
 * hb_mc_device_program_init() or hb_mc_device_program_init_binary() should
 * have been called before calling this function to set up a memory allocator.
 * @param[in]  device        Pointer to device
 * @param[out] eva           Eva address of the memory to HE freed
 * @return HB_MC_SUCCESS if succesful. Otherwise an error code is returned.
 */
int hb_mc_device_free (hb_mc_device_t *device, hb_mc_eva_t eva)
{
        RacEr_pr_dbg("%s: calling replicated\n", __func__);
        hb_mc_pod_id_t pod;
        hb_mc_device_foreach_pod_id(device, pod)
        {
                RACER_CUDA_CALL(hb_mc_device_pod_free(device, pod, eva));
        }
        return HB_MC_SUCCESS;
}





/**
 * Enqueues and schedules a kernel to HE run on device
 * Takes the grid size, tile group dimensions, kernel name, argc,
 * argv* and the finish signal address, calls hb_mc_tile_group_enqueue
 * to initialize all tile groups for grid.
 * @param[in]  device        Pointer to device
 * @param[in]  grid_dim      X/Y dimensions of the grid to HE initialized
 * @param[in]  tg_dim        X/Y dimensions of tile groups in grid
 * @param[in]  name          Kernel name to HE executed on tile groups in grid
 * @param[in]  argc          Number of input arguments to kernel
 * @param[in]  argv          List of input arguments to kernel
 * @return HB_MC_SUCCESS if succesful. Otherwise an error code is returned.
 */
int hb_mc_kernel_enqueue (hb_mc_device_t *device,
                          hb_mc_dimension_t grid_dim,
                          hb_mc_dimension_t tg_dim,
                          const char *name,
                          const uint32_t argc,
                          const uint32_t *argv)
{
        RacEr_pr_dbg("%s: calling replicated\n", __func__);
        hb_mc_pod_id_t pod;
        hb_mc_device_foreach_pod_id(device, pod)
        {
                RACER_CUDA_CALL(hb_mc_device_pod_kernel_enqueue(device, pod,
                                                              grid_dim,
                                                              tg_dim,
                                                              name, argc, argv));
        }
        return HB_MC_SUCCESS;
}




/**
 * Iterates over all tile groups inside device,
 * allocates those that fit in mesh and launches them.
 * API remains in this function until all tile groups
 * have successfully finished execution.
 * @param[in]  device        Pointer to device
 * @return HB_MC_SUCCESS if succesful. Otherwise an error code is returned.
 */
int hb_mc_device_tile_groups_execute (hb_mc_device_t *device)
{
        RacEr_pr_dbg("%s: calling replicated\n", __func__);
        hb_mc_pod_id_t pod;
        RACER_CUDA_CALL(hb_mc_device_pods_kernels_execute(device));
        return HB_MC_SUCCESS;
}
