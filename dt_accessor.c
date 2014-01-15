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
#include <stddef.h>
#include "dt_core.h"

dt_t
dt_from_cjdn(int n) {
    return dt_from_rdn(n - 1721425);
}

int
dt_cjdn(dt_t dt) {
    return dt_rdn(dt) + 1721425;
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
dt_doy(dt_t dt) {
    int d;
    dt_to_yd(dt, NULL, &d);
    return d;
}

int
dt_doq(dt_t dt) {
    int d;
    dt_to_yqd(dt, NULL, NULL, &d);
    return d;
}

int
dt_dom(dt_t dt) {
    int d;
    dt_to_ymd(dt, NULL, NULL, &d);
    return d;
}

int
dt_woy(dt_t dt) {
    int w;
    dt_to_ywd(dt, NULL, &w, NULL);
    return w;
}

int
dt_yow(dt_t dt) {
    int y;
    dt_to_ywd(dt, &y, NULL, NULL);
    return y;
}

