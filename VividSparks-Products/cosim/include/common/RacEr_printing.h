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

#ifndef _RACER_PRINTING_H
#define _RACER_PRINTING_H

#ifdef __cplusplus
#include <cstdint>
#include <cstddef>
#else
#include <stdint.h>
#include <stddef.h>
#endif

#include <sys/time.h>
#if defined(__cplusplus)
extern "C" {
#endif // #if defined(__cplusplus)

#define RACER_PRINT_PREFIX_DEBUG_PL "DEBUG-PL: "
#define RACER_PRINT_PREFIX_DEBUG_PS "DEBUG-PS: "
#define RACER_PRINT_PREFIX_ERROR "ERROR:   "
#define RACER_PRINT_PREFIX_WARN "WARNING: "
#define RACER_PRINT_PREFIX_INFO "INFO:    "

#if defined(ZYNQ_PL_DEBUG)
#define RacEr_pr_dbg_pl(fmt, ...)                                                \
    do {                                                                         \
        RacEr_pr_info(RACER_PRINT_PREFIX_DEBUG_PL fmt, ##__VA_ARGS__);                 \
    } while (0)
#else
#define RacEr_pr_dbg_pl(...)
#endif

#if defined(ZYNQ_PS_DEBUG)
#define RacEr_pr_dbg_ps(fmt, ...)                                                \
    do {                                                                         \
        printf(RACER_PRINT_PREFIX_DEBUG_PS fmt, ##__VA_ARGS__);                      \
    } while (0)
#else
#define RacEr_pr_dbg_ps(...)
#endif

#define RacEr_pr_err(fmt, ...)                                                   \
    do {                                                                         \
        printf(RACER_PRINT_PREFIX_ERROR fmt, ##__VA_ARGS__);                         \
    } while (0)

#define RacEr_pr_warn(fmt, ...)                                                  \
    do {                                                                         \
        printf(RACER_PRINT_PREFIX_WARN fmt, ##__VA_ARGS__);                          \
    } while (0)

#define RacEr_pr_info(fmt, ...)                                                  \
    do {                                                                         \
        printf(RACER_PRINT_PREFIX_INFO fmt, ##__VA_ARGS__);                          \
    } while (0)

#if defined(__cplusplus)
}
#endif // #if defined(__cplusplus)

#endif
