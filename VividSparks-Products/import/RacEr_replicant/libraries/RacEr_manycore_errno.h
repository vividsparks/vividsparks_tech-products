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

#ifndef RACER_MANYCORE_ERRNO
#define RACER_MANYCORE_ERRNO
#include <RacEr_manycore_features.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HB_MC_SUCCESS       (0)
#define HB_MC_FAIL          (-1)
#define HB_MC_TIMEOUT       (-2)
#define HB_MC_UNINITIALIZED (-3)
#define HB_MC_INVALID       (-4)
#define HB_MC_INITIALIZED_TWICE (-4) // same as invalid
#define HB_MC_NOMEM         (-5)
#define HB_MC_NOIMPL        (-6)
#define HB_MC_NOTFOUND      (-7)
#define HB_MC_BUSY          (-8)
#define HB_MC_UNALIGNED     (-9)
#define HB_MC_IOVERFLOW    (-10)

        static inline const char * hb_mc_strerror(int err)
        {
                static const char *strtab [] = {
                        [-HB_MC_SUCCESS]           = "Success",
                        [-HB_MC_FAIL]              = "Failure",
                        [-HB_MC_TIMEOUT]           = "Timeout",
                        [-HB_MC_UNINITIALIZED]     = "Not initialized",
                        [-HB_MC_INVALID]           = "Invalid input",
                        [-HB_MC_NOMEM]             = "Out of memory",
                        [-HB_MC_NOIMPL]            = "Not implemented",
                        [-HB_MC_NOTFOUND]          = "Not found",
                        [-HB_MC_BUSY]              = "Busy",
                        [-HB_MC_UNALIGNED]         = "Unaligned memory request",
                        [-HB_MC_IOVERFLOW]         = "Integer overflow",
                };
                return strtab[-err];
        }

        static inline int hb_mc_is_error(int err)
        {
                return (err < HB_MC_SUCCESS) && (err >= HB_MC_NOTFOUND);
        }

#ifdef __cplusplus
}
#endif

#endif
