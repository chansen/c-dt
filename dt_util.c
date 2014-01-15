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

bool
dt_leap_year(int y) {
    return ((y & 3) == 0 && (y % 100 != 0 || y % 400 == 0));
}

int
dt_days_in_year(int y) {
    return dt_leap_year(y) ? 366 : 365;
}

int
dt_days_in_quarter(int y, int q) {
    static const int days_in_quarter[2][5] = {
        { 0, 90, 91, 92, 92 },
        { 0, 91, 91, 92, 92 }
    };
    if (q < 1 || q > 4)
        return 0;
    return days_in_quarter[dt_leap_year(y)][q];
}

int
dt_days_in_month(int y, int m) {
    static const int days_in_month[2][13] = {
        { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
        { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
    };
    if (m < 1 || m > 12)
        return 0;
    return days_in_month[dt_leap_year(y)][m];
}

int
dt_weeks_in_year(int year) {
    unsigned int y, d;
    if (year < 1)
        year += 400 * (1 - year/400);
    y = year - 1;
    d = (y + y/4 - y/100 + y/400) % 7; /* Mon = 0, ... Sun = 6 */
    return (d == 3 || (d == 2 && dt_leap_year(year))) ? 53 : 52;
}

