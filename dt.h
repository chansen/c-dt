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
#ifndef __DT_H__
#define __DT_H__
#include "dt_core.h"
#include "dt_easter.h"
#include "dt_parse.h"
#include "dt_search.h"
#include "dt_tm.h"
#include "dt_util.h"
#include "dt_valid.h"
#include "dt_weekday.h"
#include "dt_workday.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    DT_EXCESS,
    DT_LIMIT,
    DT_SNAP
} dt_adjust_t;

dt_t    dt_from_cjdn            (int n);

int     dt_cjdn                 (dt_t dt);

int     dt_year                 (dt_t dt);
int     dt_quarter              (dt_t dt);
int     dt_month                (dt_t dt);

int     dt_week_of_year         (dt_t dt);

int     dt_day_of_year          (dt_t dt);
int     dt_day_of_quarter       (dt_t dt);
int     dt_day_of_month         (dt_t dt);

dt_t    dt_start_of_year        (dt_t dt, int offset);
dt_t    dt_start_of_quarter     (dt_t dt, int offset);
dt_t    dt_start_of_month       (dt_t dt, int offset);
dt_t    dt_start_of_week        (dt_t dt, int first_dow);

dt_t    dt_end_of_year          (dt_t dt, int offset);
dt_t    dt_end_of_quarter       (dt_t dt, int offset);
dt_t    dt_end_of_month         (dt_t dt, int offset);
dt_t    dt_end_of_week          (dt_t dt, int first_dow);

dt_t    dt_nth_day_of_week      (dt_t dt, int nth, int dow);

dt_t    dt_next_day_of_week     (dt_t dt, int dow, bool current);
dt_t    dt_prev_day_of_week     (dt_t dt, int dow, bool current);

dt_t    dt_add_years            (dt_t dt, int delta, dt_adjust_t adjust);
dt_t    dt_add_quarters         (dt_t dt, int delta, dt_adjust_t adjust);
dt_t    dt_add_months           (dt_t dt, int delta, dt_adjust_t adjust);

void    dt_delta_yd             (dt_t start, dt_t end, int *y, int *d);
void    dt_delta_ymd            (dt_t start, dt_t end, int *y, int *m, int *d);
void    dt_delta_yqd            (dt_t start, dt_t end, int *y, int *q, int *d);

void    dt_delta_md             (dt_t start, dt_t end, int *m, int *d);
void    dt_delta_qd             (dt_t start, dt_t end, int *q, int *d);

int     dt_delta_years          (dt_t start, dt_t end, bool complete);
int     dt_delta_quarters       (dt_t start, dt_t end, bool complete);
int     dt_delta_months         (dt_t start, dt_t end, bool complete);
int     dt_delta_weeks          (dt_t start, dt_t end);

#ifdef __cplusplus
}
#endif
#endif
