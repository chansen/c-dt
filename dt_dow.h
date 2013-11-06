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
#ifndef __DT_DOW_H__
#define __DT_DOW_H__
#include "dt_core.h"

#ifdef __cplusplus
extern "C" {
#endif

dt_t    dt_from_nth_dow_in_year     (int y, int nth, dt_dow_t day);
dt_t    dt_from_nth_dow_in_quarter  (int y, int q, int nth, dt_dow_t day);
dt_t    dt_from_nth_dow_in_month    (int y, int m, int nth, dt_dow_t day);

dt_t    dt_nth_dow                  (dt_t dt, int nth, dt_dow_t day);
dt_t    dt_nth_dow_in_year          (dt_t dt, int nth, dt_dow_t day);
dt_t    dt_nth_dow_in_quarter       (dt_t dt, int nth, dt_dow_t day);
dt_t    dt_nth_dow_in_month         (dt_t dt, int nth, dt_dow_t day);

dt_t    dt_next_dow                 (dt_t dt, dt_dow_t day, bool current);
dt_t    dt_prev_dow                 (dt_t dt, dt_dow_t day, bool current);

int     dt_dow_in_year              (dt_t dt, bool end);
int     dt_dow_in_quarter           (dt_t dt, bool end);
int     dt_dow_in_month             (dt_t dt, bool end);

bool    dt_is_nth_dow_in_year       (dt_t dt, int nth, dt_dow_t day);
bool    dt_is_nth_dow_in_quarter    (dt_t dt, int nth, dt_dow_t day);
bool    dt_is_nth_dow_in_month      (dt_t dt, int nth, dt_dow_t day);

#ifdef __cplusplus
}
#endif
#endif

