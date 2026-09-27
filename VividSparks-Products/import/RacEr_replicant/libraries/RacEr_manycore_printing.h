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

#ifndef _RACER_MANYCORE_PRINTING_H
#define _RACER_MANYCORE_PRINTING_H
#include <RacEr_manycore_features.h>

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


#define RACER_PRINT_PREFIX_DEBUG "DEBUG"
#define RACER_PRINT_PREFIX_ERROR "ERROR:   "
#define RACER_PRINT_PREFIX_WARN  "WARNING: "
#define RACER_PRINT_PREFIX_INFO  "INFO:    "

#define RACER_PRINT_STREAM_DEBUG stderr
#define RACER_PRINT_STREAM_ERROR stderr
#define RACER_PRINT_STREAM_WARN  stderr
#define RACER_PRINT_STREAM_INFO  stderr

        static inline uint64_t RacEr_utc(){
                struct timeval tv;
                gettimeofday(&tv, NULL);

                uint64_t ms =
                        (uint64_t)(tv.tv_sec) * 1000 +
                        (uint64_t)(tv.tv_usec) / 1000;

                return ms;
        }

        __attribute__((format(printf, 2, 3)))
        int RacEr_pr_prefix(const char *prefix, const char *fmt, ...);


#if defined(DEBUG)
#define RacEr_pr_dbg(fmt, ...)                                            \
        RacEr_pr_prefix(RACER_PRINT_PREFIX_DEBUG, fmt, ##__VA_ARGS__)
#else
#define RacEr_pr_dbg(...)
#endif

#define RacEr_pr_err(fmt, ...)                                            \
        RacEr_pr_prefix(RACER_PRINT_PREFIX_ERROR, fmt, ##__VA_ARGS__)

#define RacEr_pr_warn(fmt, ...)                                           \
        RacEr_pr_prefix(RACER_PRINT_PREFIX_WARN, fmt, ##__VA_ARGS__)

#define RacEr_pr_info(fmt, ...)                                           \
        RacEr_pr_prefix(RACER_PRINT_PREFIX_INFO, fmt, ##__VA_ARGS__)


#if defined(__cplusplus)
}
#endif // #if defined(__cplusplus)

#endif
