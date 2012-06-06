/*
 * Copyright (c) 2012 Christian Hansen <chansen@cpan.org>
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
 *
 * <https://github.com/chansen/c-dt>
 */
#ifndef __DT_H__
#define __DT_H__

#include <time.h>
#include <stdbool.h>

typedef int dt_t;

typedef enum {
    DT_MONDAY=1,
    DT_TUESDAY,
    DT_WEDNESDAY,
    DT_THURSDAY,
    DT_FRIDAY,
    DT_SATURDAY,
    DT_SUNDAY
} dt_day_of_week_t;

typedef enum {
    DT_ORTHODOX,
    DT_WESTERN
} dt_computus_t;

typedef enum {
    DT_EXCESS,
    DT_LIMIT,
    DT_SNAP
} dt_adjust_t;

#ifdef __cplusplus
extern "C" {
#endif

dt_t  dt_from_cjdn            (int n);
dt_t  dt_from_easter          (int y, dt_computus_t computus);
dt_t  dt_from_struct_tm       (const struct tm *tm);
dt_t  dt_from_yd              (int y, int d);
dt_t  dt_from_ymd             (int y, int m, int d);
dt_t  dt_from_yqd             (int y, int q, int d);
dt_t  dt_from_ywd             (int y, int w, int d);

bool  dt_valid_yd             (int y, int d);
bool  dt_valid_ymd            (int y, int m, int d);
bool  dt_valid_yqd            (int y, int q, int d);
bool  dt_valid_ywd            (int y, int w, int d);

void  dt_to_struct_tm         (dt_t dt, struct tm *tm);
void  dt_to_yd                (dt_t dt, int *y, int *d);
void  dt_to_ymd               (dt_t dt, int *y, int *m, int *d);
void  dt_to_yqd               (dt_t dt, int *y, int *q, int *d);
void  dt_to_ywd               (dt_t dt, int *y, int *w, int *d);

int   dt_cjdn                 (dt_t dt);
int   dt_year                 (dt_t dt);
int   dt_quarter              (dt_t dt);
int   dt_month                (dt_t dt);
int   dt_week                 (dt_t dt);
int   dt_day                  (dt_t dt);
int   dt_day_of_year          (dt_t dt);
int   dt_day_of_quarter       (dt_t dt);
int   dt_day_of_week          (dt_t dt);

dt_t  dt_first_day_of_year    (dt_t dt, int delta);
dt_t  dt_first_day_of_quarter (dt_t dt, int delta);
dt_t  dt_first_day_of_month   (dt_t dt, int delta);
dt_t  dt_first_day_of_week    (dt_t dt, int first_dow);

dt_t  dt_last_day_of_year     (dt_t dt, int delta);
dt_t  dt_last_day_of_quarter  (dt_t dt, int delta);
dt_t  dt_last_day_of_month    (dt_t dt, int delta);
dt_t  dt_last_day_of_week     (dt_t dt, int first_dow);

dt_t  dt_nth_day_of_week      (dt_t dt, int nth, int dow);

dt_t  dt_next_day_of_week     (dt_t dt, int dow, bool current);
dt_t  dt_prev_day_of_week     (dt_t dt, int dow, bool current);

dt_t  dt_add_quarters         (dt_t dt, int delta, dt_adjust_t adjust);
dt_t  dt_add_months           (dt_t dt, int delta, dt_adjust_t adjust);

int   dt_delta_years          (dt_t dt1, dt_t dt2);
int   dt_delta_quarters       (dt_t dt1, dt_t dt2);
int   dt_delta_months         (dt_t dt1, dt_t dt2);
int   dt_delta_weeks          (dt_t dt1, dt_t dt2);

bool  dt_leap_year            (int y);
int   dt_days_in_year         (int y);
int   dt_days_in_quarter      (int y, int q);
int   dt_days_in_month        (int y, int m);

#ifdef __cplusplus
}
#endif
#endif
