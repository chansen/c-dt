/*
 * Copyright (c) 2012-2015 Christian Hansen <chansen@cpan.org>
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
#ifndef __DT_WORKDAY_H__
#define __DT_WORKDAY_H__
#include <stddef.h>
#include "dt_core.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    DT_UNADJUSTED,
    DT_FOLLOWING,
    DT_MODIFIED_FOLLOWING,
    DT_PRECEDING,
    DT_MODIFIED_PRECEDING,
} dt_bdc_t;

dt_t    dt_from_nth_workday_in_year     (int y, int nth, const dt_t *holidays, size_t n);
dt_t    dt_from_nth_workday_in_quarter  (int y, int q, int nth, const dt_t *holidays, size_t n);
dt_t    dt_from_nth_workday_in_month    (int y, int m, int nth, const dt_t *holidays, size_t n);

dt_t    dt_nth_workday_in_year          (dt_t dt, int nth, const dt_t *holidays, size_t n);
dt_t    dt_nth_workday_in_quarter       (dt_t dt, int nth, const dt_t *holidays, size_t n);
dt_t    dt_nth_workday_in_month         (dt_t dt, int nth, const dt_t *holidays, size_t n);

bool    dt_is_holiday                   (dt_t dt, const dt_t *holidays, size_t n);
bool    dt_is_workday                   (dt_t dt, const dt_t *holidays, size_t n);

dt_t    dt_next_workday                 (dt_t dt, bool current, const dt_t *holidays, size_t n);
dt_t    dt_prev_workday                 (dt_t dt, bool current, const dt_t *holidays, size_t n);

dt_t    dt_add_workdays                 (dt_t dt, int delta, const dt_t *holidays, size_t n);

int     dt_delta_workdays               (dt_t start, dt_t end, bool inclusive, const dt_t *holidays, size_t n);

dt_t    dt_roll_workday                 (dt_t dt, dt_bdc_t convention, const dt_t *holidays, size_t n);

#ifdef __cplusplus
}
#endif
#endif

