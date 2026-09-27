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

#include <RacEr_manycore_features.h>
#include <RacEr_manycore_epa.h>
#include <cstddef>
#include <RacEr_manycore_errno.h>

/**
 * Checks alignment of an epa based on data size in bytes.
 * @param[in] epa  epa address
 * @param[in] sz   data size in bytes.
 * @return         HB_MC_SUCCESS if npa is aligned and HB_MC_UNALIGNED if not,
 *                 and HB_MC_INVALID otherwise.
 */
int hb_mc_manycore_epa_check_alignment(const hb_mc_epa_t *epa, size_t sz)
{
        switch (sz) {
        case 4:
                if (*epa & 0x3)
                        return HB_MC_UNALIGNED;
                break;
        case 2:
                if (*epa & 0x1)
                        return HB_MC_UNALIGNED;
                break;
        case 1:
                break;
        default:
                return HB_MC_INVALID;
        }
        return HB_MC_SUCCESS;
}
