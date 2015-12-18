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
#include "dt_core.h"
#include "dt_easter.h"

/* 
 * Easter algorithms by Al Petrofsky, San Mateo County, California, U.S.A. 
 * <http://petrofsky.org/>
 */
static int
easter_gregorian(unsigned int y) {
    unsigned int a, b;
    a = y/100 * 1483 - y/400 * 2225 + 2613;
    b = ((y % 19 * 3510 + a/25 * 319) / 330) % 29;
    return 56 - b - ((y * 5/4) + a - b) % 7;
}

static int
easter_julian(unsigned int y) {
    unsigned int a;
    a = (y % 19 * 19 + 15) % 30;
    return 28 + a - ((y * 5/4) + a) % 7;
}

dt_t
dt_from_easter(int y, dt_computus_t computus) {
    if (y < 1)
        return 0;
    if (computus == DT_WESTERN)
        return dt_from_ymd(y, 3, easter_gregorian(y));
    else
        return dt_from_ymd(y, 3, easter_julian(y) + y/100 - y/400 - 2);
}

