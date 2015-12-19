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
#ifndef __DT_ZONE_H__
#define __DT_ZONE_H__
#include <stddef.h>
#include "dt_core.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    DT_ZONE_UTC       = 0x01,
    DT_ZONE_RFC       = 0x02,
    DT_ZONE_MILITARY  = 0x04,
    DT_ZONE_AMBIGUOUS = 0x08,
};

typedef struct {
    char name[8];
    unsigned short flags;
    short offset;
} dt_zone_t;

size_t          dt_zone_lookup          (const char *str, size_t len, const dt_zone_t **zone);
const char *    dt_zone_name            (const dt_zone_t *zone);
short           dt_zone_offset          (const dt_zone_t *zone);
bool            dt_zone_is_utc          (const dt_zone_t *zone);
bool            dt_zone_is_rfc          (const dt_zone_t *zone);
bool            dt_zone_is_military     (const dt_zone_t *zone);
bool            dt_zone_is_ambiguous    (const dt_zone_t *zone);

#ifdef __cplusplus
}
#endif
#endif
