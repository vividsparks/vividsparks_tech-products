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

#include <RacEr_manycore_printing.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include <map>
#include <string>

using std::map;
using std::string;

typedef struct prefix_info {
        FILE *file;
        bool newline;
        void (*newline_hook)(struct prefix_info *info, const char *prefix);
} prefix_info_t;

/* inserts the time into the prefix */
static void insert_time(prefix_info_t *info, const char *prefix)
{
        fprintf(info->file, "%s @ (%lu): ", prefix, RacEr_utc());
        return;
}

typedef map<string, prefix_info_t> prefix_map;

static prefix_map fmap = {
        {RACER_PRINT_PREFIX_DEBUG, {RACER_PRINT_STREAM_DEBUG, true, insert_time}},
        {RACER_PRINT_PREFIX_ERROR, {RACER_PRINT_STREAM_ERROR, true, 0}},
        {RACER_PRINT_PREFIX_WARN,  {RACER_PRINT_STREAM_WARN,  true, 0}},
        {RACER_PRINT_PREFIX_INFO,  {RACER_PRINT_STREAM_INFO,  true, 0}},
};

int RacEr_pr_prefix(const char *prefix, const char *fmt, ...)
{
        string prefix_string(prefix);
        string fmt_string(fmt);
        prefix_info_t *info;
        va_list ap;
        int r = -1, count = 0;
        bool newline;

        auto it = fmap.find(prefix_string);
        if (it != fmap.end()) {
                info = &it->second;
        } else {
                return r;
        }

        // lock our file to make our print atomic
        flockfile(info->file);
        va_start(ap, fmt);
        newline = info->newline;

        string::size_type  cl_start = 0, cl_end;
        do { // for each line in fmt
                // find end of line
                cl_end = fmt_string.find('\n', cl_start);
                cl_end = (cl_end == string::npos ? fmt_string.size() : cl_end);

                // print prefix if this is the start of a new line
                if (newline) {
                        if (info->newline_hook) {
                                info->newline_hook(info, prefix);
                        } else {
                                fprintf(info->file, "%s", prefix);
                        }
                }

                // print to the end of the line
                string lfmt = fmt_string.substr(cl_start, cl_end-cl_start);

                count += vfprintf(info->file, lfmt.c_str(), ap);

                // move cl_start forward
                cl_start = cl_end;

                // decide on newline
                if (cl_end != fmt_string.size()) {
                        // print the newline character and set 'newline' to true
                        count += fprintf(info->file, "\n");
                        cl_start++; // advance one so we don't print the 'newline' twice
                        newline = true;
                } else {
                        // this was the last line printed
                        // if it was an empty line just set newline to false
                        newline = lfmt.empty() ? true : false;
                }

                // until we've reached the end of our format string
        } while (cl_start < fmt_string.size());

        // success
        r = count;

 exit_func:
        // setup for the next call
        info->newline = newline;
        va_end(ap);
        funlockfile(info->file);
        return r;
}
