/*
 * Copyright (c) 2012-2013 Christian Hansen <chansen@cpan.org>
 * <https://github.com/chansen/c-dt>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met: 
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "dt_core.h"
#include "dt_adjust.h"
#include "dt_workday.h"

dt_t
dt_adjust(dt_t dt, dt_bdc_t convention, const dt_t *holidays, size_t n) {
    dt_t start;
    int y, m;
    
    start = dt;
    switch (convention) {
        case DT_UNADJUSTED:
            break;
        case DT_FOLLOWING:
            dt = dt_next_workday(dt, true, holidays, n);
            break;
        case DT_MODIFIED_FOLLOWING:
            dt = dt_next_workday(dt, true, holidays, n);
            if (dt != start) {
                dt_to_ymd(start, &y, &m, NULL);
                if (dt > dt_from_ymd(y, m + 1, 0))
                    dt = dt_prev_workday(start, false, holidays, n);
            }
            break;
        case DT_PRECEDING:
            dt = dt_prev_workday(dt, true, holidays, n);
            break;
        case DT_MODIFIED_PRECEDING:
            dt = dt_prev_workday(dt, true, holidays, n);
            if (dt != start) {
                dt_to_ymd(start, &y, &m, NULL);
                if (dt < dt_from_ymd(y, m, 1))
                    dt = dt_next_workday(start, false, holidays, n);
            }
            break;
    }
    return dt;
}
