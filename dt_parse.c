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
#include "dt_valid.h"

static size_t
count_digits(const unsigned char * const p, size_t i, const size_t len) {
    size_t n = i;

    for(; i < len; i++) {
        const unsigned char c = p[i];
        if (c < '0' || c > '9')
            break;
    }
    return i - n;
}

static int
parse_number(const unsigned char * const p, size_t i, const size_t len) {
    int v = 0;

    switch (len) {
        case 4: v += (p[i++] - '0') * 1000;
        case 3: v += (p[i++] - '0') * 100;
        case 2: v += (p[i++] - '0') * 10;
        case 1: v += (p[i++] - '0');
    }
    return v;
}

/*
 *  Basic      Extended
 *  20121224   2012-12-24   Calendar date   (ISO 8601)
 *  2012359    2012-359     Ordinal date    (ISO 8601)
 *  2012W521   2012-W52-1   Week date       (ISO 8601)
 *  2012Q485   2012-Q4-85   Quarter date
 */
size_t
dt_parse_string(const char *str, size_t len, dt_t *dtp) {
    const unsigned char *p;
    int y, x, d;
    size_t n;
    dt_t dt;

    p = (const unsigned char *)str;
    n = count_digits(p, 0, len);
    switch (n) {
        case 4: /* 2012 (year) */
            y = parse_number(p, 0, 4);
            break;
        case 7: /* 2012359 (basic ordinal date) */
            y = parse_number(p, 0, 4);
            d = parse_number(p, 4, 3);
            goto yd;
        case 8: /* 20121224 (basic calendar date) */
            y = parse_number(p, 0, 4);
            x = parse_number(p, 4, 2);
            d = parse_number(p, 6, 2);
            goto ymd;
        default:
            return 0;
    }

    if (len < 8)
        return 0;

    n = count_digits(p, 5, len);
    switch (p[4]) {
        case '-': /* 2012-359 | 2012-12-24 | 2012-W52-1 | 2012-Q4-85 */
            break;
#ifndef DT_STRICT_ISO8601
        case 'Q': /* 2012Q485 */
            if (n != 3)
                return 0;
            x = parse_number(p, 5, 1);
            d = parse_number(p, 6, 2);
            n = 8;
            goto yqd;
#endif
        case 'W': /* 2012W521 */
            if (n != 3)
                return 0;
            x = parse_number(p, 5, 2);
            d = parse_number(p, 7, 1);
            n = 8;
            goto ywd;
        default:
            return 0;
    }

    switch (n) {
        case 0: /* 2012-Q4-85 | 2012-W52-1 */
            break;
        case 2: /* 2012-12-24 */
            if (p[7] != '-' || count_digits(p, 8, len) != 2)
                return 0;
            x = parse_number(p, 5, 2);
            d = parse_number(p, 8, 2);
            n = 10;
            goto ymd;
        case 3: /* 2012-359 */
            d = parse_number(p, 5, 3);
            n = 8;
            goto yd;
        default:
            return 0;
    }

    if (len < 10)
        return 0;

    n = count_digits(p, 6, len);
    switch (p[5]) {
#ifndef DT_STRICT_ISO8601
        case 'Q': /* 2012-Q4-85 */
            if (n != 1 || p[7] != '-' || count_digits(p, 8, len) != 2)
                return 0;
            x = parse_number(p, 6, 1);
            d = parse_number(p, 8, 2);
            n = 10;
            goto yqd;
#endif
        case 'W': /* 2012-W52-1 */
            if (n != 2 || p[8] != '-' || count_digits(p, 9, len) != 1)
                return 0;
            x = parse_number(p, 6, 2);
            d = parse_number(p, 9, 1);
            n = 10;
            goto ywd;
        default:
            return 0;
    }

  yd:
    if (!dt_valid_yd(y, d))
        return 0;
    dt = dt_from_yd(y, d);
    goto finish;

  ymd:
    if (!dt_valid_ymd(y, x, d))
        return 0;
    dt = dt_from_ymd(y, x, d);
    goto finish;

#ifndef DT_STRICT_ISO8601
  yqd:
    if (!dt_valid_yqd(y, x, d))
        return 0;
    dt = dt_from_yqd(y, x, d);
    goto finish;
#endif

  ywd:
    if (!dt_valid_ywd(y, x, d))
        return 0;
    dt = dt_from_ywd(y, x, d);

  finish:
#ifndef DT_PARSE_YEAR0
    if (y < 1)
        return 0;
#endif
    if (dtp)
        *dtp = dt;
    return n;
}

