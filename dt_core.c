/*
 * Copyright (c) 2012-2014 Christian Hansen <chansen@cpan.org>
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
#include <assert.h>
#include "dt_core.h"

#define LEAP_YEAR(y) \
    (((y) & 3) == 0 && ((y) % 100 != 0 || (y) % 400 == 0))

#define DAYS_IN_YEAR(y) \
    (LEAP_YEAR(y) ? 366 : 365)

static const int days_preceding_month[2][13] = {
    { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 },
    { 0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 }
};

static const int days_preceding_quarter[2][5] = {
    { 0, 0, 90, 181, 273 },
    { 0, 0, 91, 182, 274 }
};

dt_t
dt_from_rdn(int n) {
    return n + DT_EPOCH_OFFSET;
}

dt_t
dt_from_yd(int y, int d) {
    y--;
    if (y < 0) {
        const int n400 = 1 - y/400;
        y += n400 * 400;
        d -= n400 * 146097;
    }
    return 365 * y + y/4 - y/100 + y/400 + d + DT_EPOCH_OFFSET;
}

dt_t
dt_from_ymd(int y, int m, int d) {
    if (m < 1 || m > 12) {
        y += m / 12;
        m %= 12;
        if (m < 1)
            y--, m += 12;
    }
    assert(m >=  1);
    assert(m <= 12);
    return dt_from_yd(y, days_preceding_month[LEAP_YEAR(y)][m] + d);
}

dt_t
dt_from_yqd(int y, int q, int d) {
    if (q < 1 || q > 4) {
        y += q / 4;
        q %= 4;
        if (q < 1)
            y--, q += 4;
    }
    assert(q >= 1);
    assert(q <= 4);
    return dt_from_yd(y, days_preceding_quarter[LEAP_YEAR(y)][q] + d);
}

dt_t
dt_from_ywd(int y, int w, int d) {
    dt_t dt;

    dt  = dt_from_yd(y, 4);
    dt -= dt_dow(dt);
    dt += w * 7 + d - 7;
    return dt;
}


#ifndef DT_NO_SHORTCUTS
static const dt_t DT1901 = 693961 + DT_EPOCH_OFFSET; /* 1901-01-01 */
static const dt_t DT2099 = 766644 + DT_EPOCH_OFFSET; /* 2099-12-31 */
#endif

void
dt_to_yd(dt_t d, int *yp, int *dp) {
    int y, n100, n1;

    y = 0;
#ifndef DT_NO_SHORTCUTS
    /* Shortcut dates between the years 1901-2099 inclusive */
    if (d >= DT1901 && d <= DT2099) {
        d -= DT1901 - 1;
        y += (4 * d - 1) / 1461;
        d -= (1461 * y) / 4;
        y += 1901;
    }
    else
#endif
    {
        d -= DT_EPOCH_OFFSET;
        if (d < 1) {
            const int n400 = 1 - d/146097;
            y -= n400 * 400;
            d += n400 * 146097;
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
    m = doy < 32 ? 1 : 1 + (5 * (doy - 59 - l) + 303) / 153;

    assert(m >=  1);
    assert(m <= 12);

    if (yp) *yp = y;
    if (mp) *mp = m;
    if (dp) *dp = doy - days_preceding_month[l][m];
}

void
dt_to_yqd(dt_t dt, int *yp, int *qp, int *dp) {
    int y, doy, q, l;

    dt_to_yd(dt, &y, &doy);
    l = LEAP_YEAR(y);
    q = doy < 91 ? 1 : 1 + (5 * (doy - 59 - l) + 303) / 459;

    assert(q >= 1);
    assert(q <= 4);

    if (yp) *yp = y;
    if (qp) *qp = q;
    if (dp) *dp = doy - days_preceding_quarter[l][q];
}

void
dt_to_ywd(dt_t dt, int *yp, int *wp, int *dp) {
    int y, doy, dow;

    dt_to_yd(dt, &y, &doy);
    dow = dt_dow(dt);
    doy = doy + 4 - dow;
    if (doy < 1) {
        y--;
        doy += DAYS_IN_YEAR(y);
    }
    else if (doy > 365) {
        const int diy = DAYS_IN_YEAR(y);
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
dt_rdn(dt_t dt) {
    return dt - DT_EPOCH_OFFSET;
}

dt_dow_t
dt_dow(dt_t dt) {
    int dow = (dt - DT_EPOCH_OFFSET) % 7;
    if (dow < 1)
        dow += 7;
    assert(dow >= 1);
    assert(dow <= 7);
    return dow;
}

