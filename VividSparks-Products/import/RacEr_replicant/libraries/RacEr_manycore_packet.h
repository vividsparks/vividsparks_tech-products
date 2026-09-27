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

#ifndef RACER_MANYCORE_PACKET_H
#define RACER_MANYCORE_PACKET_H

#include <RacEr_manycore_features.h>
#include <RacEr_manycore_request_packet.h>
#include <RacEr_manycore_response_packet.h>

#ifdef __cplusplus
extern "C" {
#endif

        typedef union packet {
                hb_mc_request_packet_t request; /**/
                hb_mc_response_packet_t response; /* from the Hammerblade Manycore */
                uint32_t words[4];
        } __attribute__((aligned(4))) hb_mc_packet_t;

        /**
         * Fill a response packet fields using a request packet.
         * @param[out] rsp a response packet
         * @param[in] req a request packet
         */
        static void hb_mc_response_packet_fill(hb_mc_response_packet_t *rsp,
                                               const hb_mc_request_packet_t *req)
        {
                hb_mc_response_packet_set_y_dst(rsp, hb_mc_request_packet_get_y_src(req));
                hb_mc_response_packet_set_x_dst(rsp, hb_mc_request_packet_get_x_src(req));
                hb_mc_response_packet_set_op(rsp, hb_mc_request_packet_get_op(req));
                hb_mc_response_packet_set_load_id(rsp, hb_mc_request_packet_get_load_id(req));
                return;
        }

#ifdef __cplusplus
}
#endif
#endif
