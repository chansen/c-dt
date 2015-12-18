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
#include <stddef.h>
#include "dt_core.h"
#include "dt_util.h"
#include "dt_dow.h"

dt_t
dt_from_nth_dow_in_year(int y, int nth, dt_dow_t day) {
    dt_t dt;

    if (nth > 0) {
        dt = dt_nth_dow(dt_from_yd(y, 1), nth, day);
        if (nth <= 52 || dt <= dt_from_yd(y + 1, 0))
            return dt;
    }
    else if (nth < 0) {
        dt = dt_nth_dow(dt_from_yd(y + 1, 0), nth, day);
        if (nth >= -52 || dt >= dt_from_yd(y, 1))
            return dt;
    }
    return 0;
}

dt_t
dt_from_nth_dow_in_quarter(int y, int q, int nth, dt_dow_t day) {
    dt_t dt;

    if (nth > 0) {
        dt = dt_nth_dow(dt_from_yqd(y, q, 1), nth, day);
        if (nth <= 12 || dt <= dt_from_yqd(y, q + 1, 0))
            return dt;
    }
    else if (nth < 0) {
        dt = dt_nth_dow(dt_from_yqd(y, q + 1, 0), nth, day);
        if (nth >= -12 || dt >= dt_from_yqd(y, q, 1))
            return dt;
    }
    return 0;
}

dt_t
dt_from_nth_dow_in_month(int y, int m, int nth, dt_dow_t day) {
    dt_t dt;

    if (nth > 0) {
        dt = dt_nth_dow(dt_from_ymd(y, m, 1), nth, day);
        if (nth <= 4 || dt <= dt_from_ymd(y, m + 1, 0))
            return dt;
    }
    else if (nth < 0) {
        dt = dt_nth_dow(dt_from_ymd(y, m + 1, 0), nth, day);
        if (nth >= -4 || dt >= dt_from_ymd(y, m, 1))
            return dt;
    }
    return 0;
}

dt_t
dt_nth_dow(dt_t dt, int nth, dt_dow_t day) {
    if      (nth > 0) nth--, dt += (day - dt_dow(dt) + 7) % 7;
    else if (nth < 0) nth++, dt -= (dt_dow(dt) - day + 7) % 7;
    return dt + nth * 7;
}

dt_t
dt_nth_dow_in_year(dt_t dt, int nth, dt_dow_t day) {
    int y;
    dt_to_yd(dt, &y, NULL);
    return dt_from_nth_dow_in_year(y, nth, day);
}

dt_t
dt_nth_dow_in_quarter(dt_t dt, int nth, dt_dow_t day) {
    int y, q;
    dt_to_yqd(dt, &y, &q, NULL);
    return dt_from_nth_dow_in_quarter(y, q, nth, day);
}

dt_t
dt_nth_dow_in_month(dt_t dt, int nth, dt_dow_t day) {
    int y, m;
    dt_to_ymd(dt, &y, &m, NULL);
    return dt_from_nth_dow_in_month(y, m, nth, day);
}

dt_t
dt_next_dow(dt_t dt, dt_dow_t day, bool current) {
    if (current) return dt + (day - dt_dow(dt) + 7) % 7;
    else         return dt + (day - dt_dow(dt) + 6) % 7 + 1;
}

dt_t
dt_prev_dow(dt_t dt, dt_dow_t day, bool current) {
    if (current) return dt - (dt_dow(dt) - day + 7) % 7;
    else         return dt - (dt_dow(dt) - day + 6) % 7 - 1;
}

int
dt_dow_in_year(dt_t dt, bool end) {
    int y, d;

    dt_to_yd(dt, &y, &d);
    if  (end) return (d - dt_days_in_year(y) - 7) / 7;
    else      return (d + 6) / 7;
}

int
dt_dow_in_quarter(dt_t dt, bool end) {
    int y, q, d;

    dt_to_yqd(dt, &y, &q, &d);
    if  (end) return (d - dt_days_in_quarter(y, q) - 7) / 7;
    else      return (d + 6) / 7;
}

int
dt_dow_in_month(dt_t dt, bool end) {
    int y, m, d;

    dt_to_ymd(dt, &y, &m, &d);
    if  (end) return (d - dt_days_in_month(y, m) - 7) / 7;
    else      return (d + 6) / 7;
}

bool
dt_is_nth_dow_in_year(dt_t dt, int nth, dt_dow_t day) {
    const bool end = (nth < 0);
    return (dt_dow(dt) == day &&
            dt_dow_in_year(dt, end) == nth);
}

bool
dt_is_nth_dow_in_quarter(dt_t dt, int nth, dt_dow_t day) {
    const bool end = (nth < 0);
    return (dt_dow(dt) == day &&
            dt_dow_in_quarter(dt, end) == nth);
}

bool
dt_is_nth_dow_in_month(dt_t dt, int nth, dt_dow_t day) {
    const bool end = (nth < 0);
    return (dt_dow(dt) == day &&
            dt_dow_in_month(dt, end) == nth);
}

