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

#ifndef RACER_MANYCORE_ORIGIN_EVA_MAP_H
#define RACER_MANYCORE_ORIGIN_EVA_MAP_H

#include <RacEr_manycore_features.h>
#include <RacEr_manycore_eva.h>
#include <RacEr_manycore_coordinate.h>
#ifdef __cplusplus
#else
#endif

#ifdef __cplusplus
extern "C" {
#endif

        /**
         * Initialize an EVA map for tiles centered at an origin.
         * @param[in] map     An EVA<->NPA map to initialize.
         * @param[in] origin  An origin tile around which the map is centered.
         * @return HB_MC_SUCCESS if succesful. Otherwise an error code is returned.
         */
        __attribute__((warn_unused_result))
        int  hb_mc_origin_eva_map_init(hb_mc_eva_map_t *map, hb_mc_coordinate_t origin);

        /**
         * Cleanup an EVA map for tiles centered at an origin.
         * @param[in] map  An EVA<->NPA map initialized with hb_mc_origin_eva_map_init().
         * @return HB_MC_SUCCESS if succesful. Otherwise an error code is returned.
         */
        __attribute__((warn_unused_result))
        int hb_mc_origin_eva_map_exit(hb_mc_eva_map_t *map);

#ifdef __cplusplus
}
#endif
#endif
