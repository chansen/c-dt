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

typedef enum {
    DT_ORTHODOX,
    DT_WESTERN,
} dt_easter_t;

typedef enum {
    DT_EXCESS,
    DT_LIMIT,
    DT_SNAP,
} dt_adjust_t;

#ifdef __cplusplus
extern "C" {
#endif

int   dt_from_cjdn            (int n);
int   dt_from_easter          (int y, dt_easter_t computus);
int   dt_from_struct_tm       (const struct tm *tm);
int   dt_from_yd              (int y, int d);
int   dt_from_ymd             (int y, int m, int d);
int   dt_from_yqd             (int y, int q, int d);
int   dt_from_ywd             (int y, int w, int d);

bool  dt_valid_yd             (int y, int d);
bool  dt_valid_ymd            (int y, int m, int d);
bool  dt_valid_yqd            (int y, int q, int d);
bool  dt_valid_ywd            (int y, int w, int d);

void  dt_to_struct_tm         (int dt, struct tm *tm);
void  dt_to_yd                (int dt, int *y, int *d);
void  dt_to_ymd               (int dt, int *y, int *m, int *d);
void  dt_to_yqd               (int dt, int *y, int *q, int *d);
void  dt_to_ywd               (int dt, int *y, int *w, int *d);

int   dt_cjdn                 (int dt);
int   dt_year                 (int dt);
int   dt_quarter              (int dt);
int   dt_month                (int dt);
int   dt_day_of_year          (int dt);
int   dt_day_of_quarter       (int dt);
int   dt_day_of_month         (int dt);
int   dt_day_of_week          (int dt);
int   dt_week_of_year         (int dt);
int   dt_year_of_week         (int dt);

int   dt_first_day_of_year    (int dt, int delta);
int   dt_first_day_of_quarter (int dt, int delta);
int   dt_first_day_of_month   (int dt, int delta);
int   dt_first_day_of_week    (int dt, int first_dow);

int   dt_last_day_of_year     (int dt, int delta);
int   dt_last_day_of_quarter  (int dt, int delta);
int   dt_last_day_of_month    (int dt, int delta);
int   dt_last_day_of_week     (int dt, int first_dow);

int   dt_nth_day_of_week      (int dt, int nth, int dow);

int   dt_next_day_of_week     (int dt, int dow, bool current);
int   dt_prev_day_of_week     (int dt, int dow, bool current);

int   dt_add_quarters         (int dt, int delta, dt_adjust_t adjust);
int   dt_add_months           (int dt, int delta, dt_adjust_t adjust);

int   dt_delta_years          (int dt1, int dt2);
int   dt_delta_quarters       (int dt1, int dt2);
int   dt_delta_months         (int dt1, int dt2);
int   dt_delta_weeks          (int dt1, int dt2);

#ifdef __cplusplus
}
#endif
#endif
