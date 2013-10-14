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

dt_t
dt_start_of_year(dt_t dt, int offset) {
    int y;
    dt_to_yd(dt, &y, NULL);
    return dt_from_yd(y + offset, 1);
}

dt_t
dt_start_of_quarter(dt_t dt, int offset) {
    int y, q;
    dt_to_yqd(dt, &y, &q, NULL);
    return dt_from_yqd(y, q + offset, 1);
}

dt_t
dt_start_of_month(dt_t dt, int offset) {
    int y, m;
    dt_to_ymd(dt, &y, &m, NULL);
    return dt_from_ymd(y, m + offset, 1);
}

dt_t
dt_start_of_week(dt_t dt, int first_dow) {
    return dt - (dt_day_of_week(dt) - first_dow + 7) % 7;
}

dt_t
dt_end_of_year(dt_t dt, int offset) {
    int y;
    dt_to_yd(dt, &y, NULL);
    return dt_from_yd(y + offset + 1, 0);
}

dt_t
dt_end_of_quarter(dt_t dt, int offset) {
    int y, q;
    dt_to_yqd(dt, &y, &q, NULL);
    return dt_from_yqd(y, q + offset + 1, 0);
}

dt_t
dt_end_of_month(dt_t dt, int offset) {
    int y, m;
    dt_to_ymd(dt, &y, &m, NULL);
    return dt_from_ymd(y, m + offset + 1, 0);
}

dt_t
dt_end_of_week(dt_t dt, int first_dow) {
    return dt + (first_dow - dt_day_of_week(dt) + 6) % 7;
}

