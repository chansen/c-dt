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
#include <stddef.h>
#include "dt_core.h"
#include "dt_util.h"
#include "dt_dow.h"

dt_t
dt_from_nth_day_of_week_in_year(int y, int nth, int dow) {
    dt_t dt;

    if (nth > 0) {
        dt = dt_nth_day_of_week(dt_from_yd(y, 1), nth, dow);
        if (nth <= 52 || dt <= dt_from_yd(y + 1, 0))
            return dt;
    }
    else if (nth < 0) {
        dt = dt_nth_day_of_week(dt_from_yd(y + 1, 0), nth, dow);
        if (nth >= -52 || dt >= dt_from_yd(y, 1))
            return dt;
    }
    return 0;
}

dt_t
dt_from_nth_day_of_week_in_quarter(int y, int q, int nth, int dow) {
    dt_t dt;

    if (nth > 0) {
        dt = dt_nth_day_of_week(dt_from_yqd(y, q, 1), nth, dow);
        if (nth <= 12 || dt <= dt_from_yqd(y, q + 1, 0))
            return dt;
    }
    else if (nth < 0) {
        dt = dt_nth_day_of_week(dt_from_yqd(y, q + 1, 0), nth, dow);
        if (nth >= -12 || dt >= dt_from_yqd(y, q, 1))
            return dt;
    }
    return 0;
}

dt_t
dt_from_nth_day_of_week_in_month(int y, int m, int nth, int dow) {
    dt_t dt;

    if (nth > 0) {
        dt = dt_nth_day_of_week(dt_from_ymd(y, m, 1), nth, dow);
        if (nth <= 4 || dt <= dt_from_ymd(y, m + 1, 0))
            return dt;
    }
    else if (nth < 0) {
        dt = dt_nth_day_of_week(dt_from_ymd(y, m + 1, 0), nth, dow);
        if (nth >= -4 || dt >= dt_from_ymd(y, m, 1))
            return dt;
    }
    return 0;
}

dt_t
dt_nth_day_of_week(dt_t dt, int nth, int dow) {
    if      (nth > 0) nth--, dt += (dow - dt_day_of_week(dt) + 7) % 7;
    else if (nth < 0) nth++, dt -= (dt_day_of_week(dt) - dow + 7) % 7;
    return dt + nth * 7;
}

dt_t
dt_nth_day_of_week_in_year(dt_t dt, int nth, int dow) {
    int y;
    dt_to_yd(dt, &y, NULL);
    return dt_from_nth_day_of_week_in_year(y, nth, dow);
}

dt_t
dt_nth_day_of_week_in_quarter(dt_t dt, int nth, int dow) {
    int y, q;
    dt_to_yqd(dt, &y, &q, NULL);
    return dt_from_nth_day_of_week_in_quarter(y, q, nth, dow);
}

dt_t
dt_nth_day_of_week_in_month(dt_t dt, int nth, int dow) {
    int y, m;
    dt_to_ymd(dt, &y, &m, NULL);
    return dt_from_nth_day_of_week_in_month(y, m, nth, dow);
}

dt_t
dt_next_day_of_week(dt_t dt, int dow, bool current) {
    if (current) return dt + (dow - dt_day_of_week(dt) + 7) % 7;
    else         return dt + (dow - dt_day_of_week(dt) + 6) % 7 + 1;
}

dt_t
dt_prev_day_of_week(dt_t dt, int dow, bool current) {
    if (current) return dt - (dt_day_of_week(dt) - dow + 7) % 7;
    else         return dt - (dt_day_of_week(dt) - dow + 6) % 7 - 1;
}

int
dt_day_of_week_in_year(dt_t dt, bool end) {
    int y, d;

    dt_to_yd(dt, &y, &d);
    if  (end) return (d - dt_days_in_year(y) - 7) / 7;
    else      return (d + 6) / 7;
}

int
dt_day_of_week_in_quarter(dt_t dt, bool end) {
    int y, q, d;

    dt_to_yqd(dt, &y, &q, &d);
    if  (end) return (d - dt_days_in_quarter(y, q) - 7) / 7;
    else      return (d + 6) / 7;
}

int
dt_day_of_week_in_month(dt_t dt, bool end) {
    int y, m, d;

    dt_to_ymd(dt, &y, &m, &d);
    if  (end) return (d - dt_days_in_month(y, m) - 7) / 7;
    else      return (d + 6) / 7;
}

bool
dt_is_nth_day_of_week_in_year(dt_t dt, int nth, int dow) {
    const bool end = (nth < 0);
    return (dt_day_of_week(dt) == dow &&
            dt_day_of_week_in_year(dt, end) == nth);
}

bool
dt_is_nth_day_of_week_in_quarter(dt_t dt, int nth, int dow) {
    const bool end = (nth < 0);
    return (dt_day_of_week(dt) == dow &&
            dt_day_of_week_in_quarter(dt, end) == nth);
}

bool
dt_is_nth_day_of_week_in_month(dt_t dt, int nth, int dow) {
    const bool end = (nth < 0);
    return (dt_day_of_week(dt) == dow &&
            dt_day_of_week_in_month(dt, end) == nth);
}

