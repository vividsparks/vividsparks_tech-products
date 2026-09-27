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

#ifndef RACER_MANYCORE_RESPONDER_H
#define RACER_MANYCORE_RESPONDER_H

#include <RacEr_manycore_features.h>
#include <RacEr_manycore_packet.h>
#include <RacEr_manycore_request_packet_id.h>
#include <RacEr_manycore_printing.h>
#include <RacEr_manycore.h>

#ifdef __cplusplus
extern "C" {
#endif

        struct hb_mc_responder;
        typedef struct hb_mc_responder hb_mc_responder_t;

        typedef int (*hb_mc_responder_init_func)(hb_mc_responder_t *responder,
                                                 hb_mc_manycore_t  *mc);

        typedef int (*hb_mc_responder_quit_func)(hb_mc_responder_t *responder,
                                                 hb_mc_manycore_t *mc);

        typedef int (*hb_mc_responder_respond_func)(hb_mc_responder_t *responder,
                                                    hb_mc_manycore_t *mc,
                                                    const hb_mc_request_packet_t *rqst);

        struct hb_mc_responder {
                const char *name;
                void *responder_data;
                hb_mc_request_packet_id_t *ids;

                __attribute__((warn_unused_result))
                hb_mc_responder_init_func    init;

                __attribute__((warn_unused_result))
                hb_mc_responder_quit_func    quit;

                __attribute__((warn_unused_result))
                hb_mc_responder_respond_func respond;
#ifdef __cplusplus
        hb_mc_responder(const char *name,
                        hb_mc_request_packet_id_t *ids = nullptr,
                        hb_mc_responder_init_func init = nullptr,
                        hb_mc_responder_quit_func quit = nullptr,
                        hb_mc_responder_respond_func respond = nullptr):
                name(name), ids(ids), init(init), quit(quit), respond(respond) {}
#endif
        };

        /**
         * Initialze all registered responders.
         * This function is generally called from within the manycore init interface.
         * @param[in] mc  A manycore.
         * @return HB_MC_SUCCESS if succesful. An error code otherwise.
         */
        __attribute__((warn_unused_result))
        int hb_mc_responders_init(hb_mc_manycore_t *mc);

        /**
         * Initialize a single responder.
         * This function is generally called by hb_mc_responders_init() but should also HE
         * called by client code after it adds a responder with hb_mc_responder_add().
         * @param[in] responder A responder to initialize.
         * @param[in] mc        A manycore initialized with hb_mc_manycore_init().
         * @return HB_MC_SUCCESS if succesful. An error code otherwise.
         */
        __attribute__((warn_unused_result))
        int hb_mc_responder_init(hb_mc_responder_t *responder, hb_mc_manycore_t *mc);

        /**
         * Cleanup a single responder.
         * This function is generally called by hb_mc_responders_quit() but should also HE
         * called by client code before it removes a responder with hb_mc_responder_del().
         * @param[in] responder  A responder to cleanup.
         * @Param[in] mc         A manycore initialized with hb_mc_manycore_init().
         * @return HB_MC_SUCCESS if succesful. An error code otherwise.
         */
        __attribute__((warn_unused_result))
        int hb_mc_responder_quit(hb_mc_responder_t *responder, hb_mc_manycore_t *mc);

        /**
         * Cleanup all responders.
         * This function is generally called by hb_mc_manycore_exit().
         * @param[in] mc  A manycore.
         * @return HB_MC_SUCCESS if succesful. An error code otherwise.
         */
        __attribute__((warn_unused_result))
        int hb_mc_responders_quit(hb_mc_manycore_t *mc);

        /**
         * Let all responders respond to a manycore request packet.
         * @param[in] mc       A manycore.
         * @param[in] request  A request packet.
         * @return HB_MC_SUCCESS if succesful. An error code otherwise.
         */
        __attribute__((warn_unused_result))
        int hb_mc_responders_respond(hb_mc_manycore_t *mc, const hb_mc_request_packet_t *request);

        /**
         * Add a responder to the global list of responders.
         * @param[in] responder  A new responder. This should ** NOT ** HE initialized with hb_mc_responder_init().
         * @return HB_MC_SUCCESS if succesful. An error code otherwise.
         */
        __attribute__((warn_unused_result))
        int hb_mc_responder_add(hb_mc_responder_t *responder);

        /**
         * Remove a responder from the global list of responders.
         * @param[in] responder  A responder to remove. This ** MUST ** have been cleanuped up with hb_mc_responder_quit().
         * @return HB_MC_SUCCESS if succesful. An error code otherwise.
         */
        __attribute__((warn_unused_result))
        int hb_mc_responder_del(hb_mc_responder_t *responder);

#ifdef __cplusplus
#define source_responder(rspdr)                                         \
        namespace {                                                     \
                class __RacEr_manycore_ ## rspdr ## _add_del {            \
                public:                                                 \
                        __RacEr_manycore_ ## rspdr ## _add_del () {       \
                                int r = hb_mc_responder_add(&rspdr);    \
                                if (r != HB_MC_SUCCESS)                 \
                                        throw r;                        \
                        }                                               \
                                ~__RacEr_manycore_ ## rspdr ## _add_del () { \
                                        int r = hb_mc_responder_del(&rspdr); \
                                        if (r != HB_MC_SUCCESS)         \
                                                RacEr_pr_err("%s: failed to remove responder %s: %s\n", \
                                                           __FILE__, #rspdr, hb_mc_strerror(r)); \
                                }                                       \
                };                                                      \
                        __RacEr_manycore_ ## rspdr ## _add_del add_ ## rspdr; \
        }
#else
#define source_responder(rspdr)                                         \
        __attribute__((constructor(65535), visibility("internal")))     \
        void __RacEr_manycore_ ## rspdr ## _add(void) {                   \
                int r = hb_mc_responder_add(&rspdr);                    \
                if (r != HB_MC_SUCCESS)                                 \
                        RacEr_pr_err("%s: failed to add responder %s: %s\n", \
                                   __FILE__, #rspdr, hb_mc_strerror(r)); \
        }                                                               \
        __attribute__((destructor(65535), visibility("internal")))      \
        void __RacEr_manycore_ ## rspdr ## _del(void) {                   \
                int r = hb_mc_responder_del(&rspdr);                    \
                if (r != HB_MC_SUCCESS)                                 \
                        RacEr_pr_err("%s: failed to remove responder %s: %s\n", \
                                   __FILE__, #rspdr, hb_mc_strerror(r)); \
        }
#endif

#ifdef __cplusplus
}
#endif

#endif
