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
#ifndef __DT_PARSE_H__
#define __DT_PARSE_H__
#include <stddef.h>
#include "dt_core.h"

#ifdef __cplusplus
extern "C" {
#endif

size_t dt_parse_iso_date          (const char *str, size_t len, dt_t *dt);

size_t dt_parse_iso_time          (const char *str, size_t len, int *sod, int *nsec);
size_t dt_parse_iso_time_basic    (const char *str, size_t len, int *sod, int *nsec);
size_t dt_parse_iso_time_extended (const char *str, size_t len, int *sod, int *nsec);

size_t dt_parse_iso_zone          (const char *str, size_t len, int *offset);
size_t dt_parse_iso_zone_basic    (const char *str, size_t len, int *offset);
size_t dt_parse_iso_zone_extended (const char *str, size_t len, int *offset);
size_t dt_parse_iso_zone_lenient  (const char *str, size_t len, int *offset);

#ifdef __cplusplus
}
#endif
#endif

