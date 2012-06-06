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
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include "dt.h"

#define LEAP_YEAR(y) \
    ((y) % 4 == 0 && ((y) % 100 != 0 || (y) % 400 == 0))

#define EPOCH_CJDN 1721425

static dt_t
days_preceding_year(int y) {
    int n = 0;

    y--;
    if (y < 0) {
        const int n400 = 1 - y/400;
        y += n400 * 400;
        n -= n400 * 146097;
    }
    return n + 365 * y + y/4 - y/100 + y/400;
}

static const int days_preceding_month_[2][13] = {
    { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 },
    { 0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 }
};

static int
days_preceding_month(int y, int m) {
    assert(m >=  1);
    assert(m <= 12);
    return days_preceding_month_[LEAP_YEAR(y)][m];
}

static const int days_preceding_quarter_[2][5] = {
    { 0, 0, 90, 181, 273 },
    { 0, 0, 91, 182, 274 }
};

static int
days_preceding_quarter(int y, int q) {
    assert(q >= 1);
    assert(q <= 4);
    return days_preceding_quarter_[LEAP_YEAR(y)][q];
}

static int
days_in_year(int y) {
    static const int days_in_year[2] = { 365, 366 };
    return days_in_year[LEAP_YEAR(y)];
}

static int
days_in_quarter(int y, int q) {
    static const int days_in_quarter[2][5] = {
        { 0, 90, 91, 92, 92 },
        { 0, 91, 91, 92, 92 }
    };
    assert(q >= 1);
    assert(q <= 4);
    return days_in_quarter[LEAP_YEAR(y)][q];
}

static int
days_in_month(int y, int m) {
    static const int days_in_month[2][13] = {
        { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
        { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
    };
    assert(m >=  1);
    assert(m <= 12);
    return days_in_month[(m == 2 && LEAP_YEAR(y))][m];
}

static int
weeks_in_year(int y) {
    static const int weeks_in_year[2] = { 52, 53 };
    const int dow = dt_day_of_week(dt_from_yd(y, 1));
    return weeks_in_year[(dow == 4 || (dow == 3 && LEAP_YEAR(y)))];
}

static void
normalize_ym(int *y, int *m) {
    if (*m < 1 || *m > 12) {
        *y += *m / 12;
        *m %= 12;
        if (*m < 1) {
            --*y;
            *m += 12;
        }
    }
}

static void
normalize_yq(int *y, int *q) {
    if (*q < 1 || *q > 4) {
        *y += *q / 4;
        *q %= 4;
        if (*q < 1) {
            --*y;
            *q += 4;
        }
    }
}

/* 
 * Easter algorithms by Al Petrofsky, San Mateo County, California, U.S.A. 
 * <http://petrofsky.org/>
 */
static int
easter_gregorian(int year) {
    unsigned int y, a, b;
    y = year % 5700000;
    a = y/100 * 1483 - y/400 * 2225 + 2613;
    b = ((y % 19 * 3510 + a/25 * 319) / 330) % 29;
    return 56 - b - ((y * 5/4) + a - b) % 7;
}

static int
easter_julian(int year) {
    unsigned int y, a;
    y = year % 532;
    a = (y % 19 * 19 + 15) % 30;
    return 28 + a - ((y * 5/4) + a) % 7;
}

dt_t
dt_from_cjdn(int n) {
    return n - EPOCH_CJDN;
}

dt_t
dt_from_easter(int y, dt_computus_t computus) {
    if (y < 1)
        return -1;
    if (computus == DT_WESTERN)
        return dt_from_ymd(y, 3, easter_gregorian(y));
    else
        return dt_from_ymd(y, 3, easter_julian(y) + y/100 - y/400 - 2);
}

dt_t
dt_from_struct_tm(const struct tm *tm) {
    return dt_from_ymd(tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
}

dt_t
dt_from_yd(int y, int d) {
    return days_preceding_year(y) + d;
}

dt_t
dt_from_ymd(int y, int m, int d) {
    normalize_ym(&y, &m);
    return dt_from_yd(y, days_preceding_month(y, m) + d);
}

dt_t
dt_from_yqd(int y, int q, int d) {
    normalize_yq(&y, &q);
    return dt_from_yd(y, days_preceding_quarter(y, q) + d);
}

dt_t
dt_from_ywd(int y, int w, int d) {
    dt_t dt;

    dt  = dt_from_yd(y, 4);
    dt -= dt_day_of_week(dt);
    dt += w * 7 + d - 7;
    return dt;
}

bool
dt_valid_yd(int y, int d) {
    return (d >= 1 && (d <= 365 || d == days_in_year(y)));
}

bool
dt_valid_ymd(int y, int m, int d) {
    return ((m >= 1 && m <= 12) && 
            (d >= 1 && (d <= 28 || d <= days_in_month(y, m))));
}

bool
dt_valid_yqd(int y, int q, int d) {
    return ((q >= 1 && q <= 4) && 
            (d >= 1 && (d <= 90 || d <= days_in_quarter(y, q))));
}

bool
dt_valid_ywd(int y, int w, int d) {
    return ((w >= 1 && (w <= 52 || w == weeks_in_year(y))) &&
            (d >= 1 && d <= 7));
}

void
dt_to_struct_tm(dt_t dt, struct tm *tm) {
    int y, m, d;

    dt_to_ymd(dt, &y, &m, &d);
    tm->tm_year = y - 1900;
    tm->tm_mon  = m - 1;
    tm->tm_mday = d;
    tm->tm_wday = dt_day_of_week(dt) % 7;
    tm->tm_yday = days_preceding_month(y, m) + d - 1;
}

#define OFF1900 693596 /* 1900-01-01 */
#define OFF2100 767009 /* 2100-12-31 */

void
dt_to_yd(dt_t d, int *yp, int *dp) {
    int y, n100, n1;

    y = 0;
#ifndef DT_NO_ASSUMPTIONS
    /* Assume most dates are between the years 1900-2100 inclusive */
    if (d >= OFF1900 && d <= OFF2100) {
        d -= OFF1900 - 1;
        y += (4 * d) / 1461;
        d -= (1461 * y - 1) / 4;
        y += 1900;
    }
    else
#endif
    {
        if (d < 1) {
            const int n400 = 1 - (d / 146097);
            y -= 400 * n400;
            d += 146097 * n400;
        }
        d--;
        y += 400 * (d / 146097);
        d %= 146097;

        n100 = d / 36524;
        y += 100 * n100;
        d %= 36524;

        y += 4 * (d / 1461);
        d %= 1461;

        n1 = d / 365;
        y += n1;
        d %= 365;

        if (n100 == 4 || n1 == 4)
            d = 366;
        else
            y++, d++;
    }
    if (yp) *yp = y;
    if (dp) *dp = (int)d;
}

void
dt_to_ymd(dt_t dt, int *yp, int *mp, int *dp) {
    int y, doy, m, l;

    dt_to_yd(dt, &y, &doy);
    l = LEAP_YEAR(y);
    m = doy < 32 ? 1 : 1 + (5 * (doy - (59 + l)) + 303) / 153;

    if (yp) *yp = y;
    if (mp) *mp = m;
    if (dp) *dp = doy - days_preceding_month_[l][m];
}

void
dt_to_yqd(dt_t dt, int *yp, int *qp, int *dp) {
    int y, doy, q, l;

    dt_to_yd(dt, &y, &doy);
    l = LEAP_YEAR(y);
    q = doy < 91 ? 1 : 1 + (5 * (doy - (59 + l)) + 303) / 459;

    if (yp) *yp = y;
    if (qp) *qp = q;
    if (dp) *dp = doy - days_preceding_quarter_[l][q];
}

void
dt_to_ywd(dt_t dt, int *yp, int *wp, int *dp) {
    int y, doy, dow;

    dt_to_yd(dt, &y, &doy);
    dow = dt_day_of_week(dt);
    doy = doy + 4 - dow;
    if (doy < 1) {
        y--;
        doy += days_in_year(y);
    }
    else if (doy > 365) {
        const int diy = days_in_year(y);
        if (doy > diy) {
            doy -= diy;
            y++;
        }
    }
    if (yp) *yp = y;
    if (wp) *wp = (doy + 6) / 7;
    if (dp) *dp = dow;
}

int
dt_cjdn(dt_t dt) {
    return dt + EPOCH_CJDN;
}

int
dt_year(dt_t dt) {
    int y;
    dt_to_yd(dt, &y, NULL);
    return y;
}

int
dt_quarter(dt_t dt) {
    int q;
    dt_to_yqd(dt, NULL, &q, NULL);
    return q;
}

int
dt_month(dt_t dt) {
    int m;
    dt_to_ymd(dt, NULL, &m, NULL);
    return m;
}

int
dt_week(dt_t dt) {
    int w;
    dt_to_ywd(dt, NULL, &w, NULL);
    return w;
}

int
dt_day(dt_t dt) {
    int d;
    dt_to_ymd(dt, NULL, NULL, &d);
    return d;
}

int
dt_day_of_year(dt_t dt) {
    int d;
    dt_to_yd(dt, NULL, &d);
    return d;
}

int
dt_day_of_quarter(dt_t dt) {
    int d;
    dt_to_yqd(dt, NULL, NULL, &d);
    return d;
}

int
dt_day_of_week(dt_t dt) {
    int dow = dt % 7;
    if (dow < 1)
        dow += 7;
    return dow;
}

dt_t
dt_first_day_of_year(dt_t dt, int delta) {
    return dt_from_yd(dt_year(dt) + delta, 1);
}

dt_t
dt_first_day_of_quarter(dt_t dt, int delta) {
    int y, q;
    dt_to_yqd(dt, &y, &q, NULL);
    return dt_from_yqd(y, q + delta, 1);
}

dt_t
dt_first_day_of_month(dt_t dt, int delta) {
    int y, m;
    dt_to_ymd(dt, &y, &m, NULL);
    return dt_from_ymd(y, m + delta, 1);
}

dt_t
dt_first_day_of_week(dt_t dt, int first_dow) {
    return dt - (dt_day_of_week(dt) - first_dow + 7) % 7;
}

dt_t
dt_last_day_of_year(dt_t dt, int delta) {
    return dt_from_yd(dt_year(dt) + delta + 1, 0);
}

dt_t
dt_last_day_of_quarter(dt_t dt, int delta) {
    int y, q;
    dt_to_yqd(dt, &y, &q, NULL);
    return dt_from_yqd(y, q + delta + 1, 0);
}

dt_t
dt_last_day_of_month(dt_t dt, int delta) {
    int y, m;
    dt_to_ymd(dt, &y, &m, NULL);
    return dt_from_ymd(y, m + delta + 1, 0);
}

dt_t
dt_last_day_of_week(dt_t dt, int first_dow) {
    return dt + (first_dow - dt_day_of_week(dt) + 6) % 7;
}

dt_t
dt_nth_day_of_week(dt_t dt, int nth, int dow) {
    if      (nth > 0) nth--, dt += (dow - dt_day_of_week(dt) + 7) % 7;
    else if (nth < 0) nth++, dt -= (dt_day_of_week(dt) - dow + 7) % 7;
    return dt + nth * 7;
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

dt_t
dt_add_quarters(dt_t dt, int delta, dt_adjust_t adjust) {
    int y, q, d;

    dt_to_yqd(dt, &y, &q, &d);
    if (adjust == DT_EXCESS || d < 91)
        return dt_from_yqd(y, q + delta, d);
    else {
        int ry = y;
        int rq = q + delta;
        int diq;

        normalize_yq(&ry, &rq);
        diq = days_in_quarter(ry, rq);
        if (d > diq || (adjust == DT_SNAP && d == days_in_quarter(y, q)))
            d = diq;
        return dt_from_yqd(ry, rq, d);
    }
}

dt_t
dt_add_months(dt_t dt, int delta, dt_adjust_t adjust) {
    int y, m, d;

    dt_to_ymd(dt, &y, &m, &d);
    if (adjust == DT_EXCESS || d < 28)
        return dt_from_ymd(y, m + delta, d);
    else {
        int ry = y;
        int rm = m + delta;
        int dim;

        normalize_ym(&ry, &rm);
        dim = days_in_month(ry, rm);
        if (d > dim || (adjust == DT_SNAP && d == days_in_month(y, m)))
            d = dim;
        return dt_from_ymd(ry, rm, d);
    }
}

int
dt_delta_years(dt_t dt1, dt_t dt2) {
    return dt_year(dt2) - dt_year(dt1);
}

int
dt_delta_quarters(dt_t dt1, dt_t dt2) {
    int y1, y2, q1, q2;
    dt_to_yqd(dt1, &y1, &q1, NULL);
    dt_to_yqd(dt2, &y2, &q2, NULL);
    return 4 * (y2 - y1) + (q2 - q1);
}

int
dt_delta_months(dt_t dt1, dt_t dt2) {
    int y1, y2, m1, m2;
    dt_to_ymd(dt1, &y1, &m1, NULL);
    dt_to_ymd(dt2, &y2, &m2, NULL);
    return 12 * (y2 - y1) + (m2 - m1);
}

int
dt_delta_weeks(dt_t dt1, dt_t dt2) {
    return dt2/7 - dt1/7;
}

bool
dt_leap_year(int y) {
    return LEAP_YEAR(y);
}

int
dt_days_in_year(int y) {
    return days_in_year(y);
}

int
dt_days_in_quarter(int y, int q) {
    if (q < 1 || q > 4)
        return 0;
    return days_in_quarter(y, q);
}

int
dt_days_in_month(int y, int m) {
    if (m < 1 || m > 12)
        return 0;
    return days_in_month(y, m);
}


