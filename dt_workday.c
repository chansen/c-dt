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
#include "dt_search.h"
#include "dt_weekday.h"
#include "dt_workday.h"

dt_t
dt_from_nth_workday_in_year(int y, int nth, const dt_t *holidays, size_t n) {
    dt_t dt;

    if (nth > 0) {
        dt = dt_add_workdays(dt_from_yd(y, 0), nth, holidays, n);
        if (dt <= dt_from_yd(y + 1, 0))
            return dt;
    }
    else if (nth < 0) {
        dt = dt_add_workdays(dt_from_yd(y + 1, 1), nth, holidays, n);
        if (dt >= dt_from_yd(y, 1))
            return dt;
    }
    return 0;
}

dt_t
dt_from_nth_workday_in_quarter(int y, int q, int nth, const dt_t *holidays, size_t n) {
    dt_t dt;

    if (nth > 0) {
        dt = dt_add_workdays(dt_from_yqd(y, q, 0), nth, holidays, n);
        if (dt <= dt_from_yqd(y, q + 1, 0))
            return dt;
    }
    else if (nth < 0) {
        dt = dt_add_workdays(dt_from_yqd(y, q + 1, 1), nth, holidays, n);
        if (dt >= dt_from_yqd(y, q, 1))
            return dt;
    }
    return 0;
}

dt_t
dt_from_nth_workday_in_month(int y, int m, int nth, const dt_t *holidays, size_t n) {
    dt_t dt;

    if (nth > 0) {
        dt = dt_add_workdays(dt_from_ymd(y, m, 0), nth, holidays, n);
        if (dt <= dt_from_ymd(y, m + 1, 0))
            return dt;
    }
    else if (nth < 0) {
        dt = dt_add_workdays(dt_from_ymd(y, m + 1, 1), nth, holidays, n);
        if (dt >= dt_from_ymd(y, m, 1))
            return dt;
    }
    return 0;
}

dt_t
dt_nth_workday_in_year(dt_t dt, int nth, const dt_t *holidays, size_t n) {
    int y;
    dt_to_yd(dt, &y, NULL);
    return dt_from_nth_workday_in_year(y, nth, holidays, n);
}

dt_t
dt_nth_workday_in_quarter(dt_t dt, int nth, const dt_t *holidays, size_t n) {
    int y, q;
    dt_to_yqd(dt, &y, &q, NULL);
    return dt_from_nth_workday_in_quarter(y, q, nth, holidays, n);
}

dt_t
dt_nth_workday_in_month(dt_t dt, int nth, const dt_t *holidays, size_t n) {
    int y, m;
    dt_to_ymd(dt, &y, &m, NULL);
    return dt_from_nth_workday_in_month(y, m, nth, holidays, n);
}

bool
dt_is_holiday(dt_t dt, const dt_t *holidays, size_t n) {
    return (n && dt_binary_search(dt, holidays, holidays + n));
}

bool
dt_is_workday(dt_t dt, const dt_t *holidays, size_t n) {
    return (dt_is_weekday(dt) && !dt_is_holiday(dt, holidays, n));
}

dt_t
dt_next_workday(dt_t dt, bool current, const dt_t *holidays, size_t n) {
    dt = dt_next_weekday(dt, current);
    while (dt_is_holiday(dt, holidays, n))
        dt = dt_next_weekday(dt, false);
    return dt;
}

dt_t
dt_prev_workday(dt_t dt, bool current, const dt_t *holidays, size_t n) {
    dt = dt_prev_weekday(dt, current);
    while (dt_is_holiday(dt, holidays, n))
        dt = dt_prev_weekday(dt, false);
    return dt;
}

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

dt_t
dt_add_workdays(dt_t dt, int delta, const dt_t *holidays, size_t n) {
    const dt_t *end, *lo, *up;

    if (!delta)
        return dt;

    if (!n)
        return dt_add_weekdays(dt, delta);

    end = holidays + n;

    if (delta > 0) {
        lo = dt_lower_bound(dt + 1, holidays, end);
        do {
            dt = dt_add_weekdays(dt, delta);
            up = dt_upper_bound(dt, lo, MIN(lo + delta, end));
            delta = up - lo;
            if (delta)
                lo = dt_lower_bound(dt, up, MIN(up + delta, end));
        } while (delta);
    }
    else {
        up = dt_upper_bound(dt - 1, holidays, end);
        do {
            dt = dt_add_weekdays(dt, delta);
            lo = dt_lower_bound(dt, MAX(up + delta, holidays), up);
            delta = lo - up;
            if (delta)
                up = dt_upper_bound(dt, MAX(lo + delta, holidays), lo);
        } while (delta);
    }
    return dt;
}

int
dt_delta_workdays(dt_t dt1, dt_t dt2, bool inclusive, const dt_t *holidays, size_t n) {
    const dt_t *end, *lo, *up;
    int delta;

    delta = dt_delta_weekdays(dt1, dt2, inclusive);
    if (!delta || !n)
        return delta;

    end = holidays + n;

    if (delta > 0) {
        lo = dt_lower_bound(dt1, holidays, end);
        up = dt_upper_bound(dt2, lo, MIN(lo + delta, end));
        delta -= up - lo;
    }
    else {
        up = dt_upper_bound(dt1, holidays, end);
        lo = dt_lower_bound(dt2, MAX(up + delta, holidays), up);
        delta -= lo - up;
    }
    return delta;
}

dt_t
dt_roll_workday(dt_t dt, dt_bdc_t convention, const dt_t *holidays, size_t n) {
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


