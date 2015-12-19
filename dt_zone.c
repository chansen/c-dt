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
#include <stddef.h>
#include <assert.h>
#include "dt_core.h"
#include "dt_zone.h"
#include "dt_char.h"

const char *
dt_zone_name(const dt_zone_t *zone) {
    return zone->name;
}

short
dt_zone_offset(const dt_zone_t *zone) {
    return zone->offset;
}

bool
dt_zone_is_utc(const dt_zone_t *zone) {
    return (zone->flags & DT_ZONE_UTC) != 0;
}

bool
dt_zone_is_rfc(const dt_zone_t *zone) {
    return (zone->flags & DT_ZONE_RFC) != 0;
}

bool
dt_zone_is_military(const dt_zone_t *zone) {
    return (zone->flags & DT_ZONE_MILITARY) != 0;
}

bool
dt_zone_is_ambiguous(const dt_zone_t *zone) {
    return (zone->flags & DT_ZONE_AMBIGUOUS) != 0;
}

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))

static const dt_zone_t kZoneEntry[] = {
    #define DT_ZONE_ENTRY(enc, offset, name, flags) \
        { name, flags, offset },
    #include "dt_zone_entries.h"
    #undef DT_ZONE_ENTRY
};

static bool
dt_zone_lookup_enc(unsigned int enc, const dt_zone_t **zone) {
    static const unsigned int T[] = {
        #define DT_ZONE_ENTRY(enc, offset, name, flags) \
            enc,
        #include "dt_zone_entries.h"
        #undef DT_ZONE_ENTRY
    };
    size_t lo, hi, mid;

    assert(ARRAY_SIZE(T) > 0);

    lo = 0;
    hi = ARRAY_SIZE(T) - 1;
    while (lo < hi) {
        mid = (lo + hi) / 2;
        if (T[mid] < enc)
            lo = mid + 1;
        else
            hi = mid;
    }

    if (lo == hi && T[lo] == enc) {
        if (zone)
            *zone = &kZoneEntry[lo];
        return true;
    }
    return false;
}

size_t
dt_zone_lookup(const char *str, size_t len, const dt_zone_t **zone) {
    const unsigned char *p = (const unsigned char *)str;
    unsigned int enc;
    size_t i;

    len = dt_char_span_alpha(p, len);
    if (!len || len > 5)
        return 0;

    enc = 0;
    for (i = 0; i < len; i++)
        enc = (enc << 5) | ((p[i] | 0x20) ^ 0x60);

    if (dt_zone_lookup_enc(enc, zone))
        return len;
    return 0;
}
