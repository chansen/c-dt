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
#include "dt_core.h"
#include "dt_util.h"

bool
dt_valid_yd(int y, int d) {
    return (d >= 1 && (d <= 365 || d == dt_days_in_year(y)));
}

bool
dt_valid_ymd(int y, int m, int d) {
    return ((m >= 1 && m <= 12) && 
            (d >= 1 && (d <= 28 || d <= dt_days_in_month(y, m))));
}

bool
dt_valid_yqd(int y, int q, int d) {
    return ((q >= 1 && q <= 4) && 
            (d >= 1 && (d <= 90 || d <= dt_days_in_quarter(y, q))));
}

bool
dt_valid_ywd(int y, int w, int d) {
    return ((d >= 1 && d <= 7) &&
            (w >= 1 && (w <= 52 || w == dt_weeks_in_year(y))));
}

