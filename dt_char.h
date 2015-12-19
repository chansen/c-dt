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
#ifndef __DT_CHAR_H__
#define __DT_CHAR_H__
#include <stddef.h>
#include "dt_core.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    DT_CHAR_HSPACE = 0x01,  /* [\t ]     */
    DT_CHAR_VSPACE = 0x02,  /* [\r\n]    */
    DT_CHAR_PUNCT  = 0x04,  /* [:punct:] */
    DT_CHAR_DIGIT  = 0x08,  /* [0-9]     */
    DT_CHAR_UPPER  = 0x10,  /* [A-Z]     */
    DT_CHAR_LOWER  = 0x20,  /* [a-z]     */
    DT_CHAR_OTHER  = 0x80,  /*           */
};

enum {
    DT_CHAR_ALPHA = DT_CHAR_UPPER  | DT_CHAR_LOWER,
    DT_CHAR_ALNUM = DT_CHAR_ALPHA  | DT_CHAR_DIGIT,
    DT_CHAR_SPACE = DT_CHAR_HSPACE | DT_CHAR_VSPACE,
    DT_CHAR_BLANK = DT_CHAR_HSPACE,
};

bool            dt_char_is_of       (unsigned char c, unsigned char mask);

bool            dt_char_is_space    (unsigned char c);
bool            dt_char_is_blank    (unsigned char c);
bool            dt_char_is_punct    (unsigned char c);
bool            dt_char_is_digit    (unsigned char c);
bool            dt_char_is_lower    (unsigned char c);
bool            dt_char_is_upper    (unsigned char c);
bool            dt_char_is_alpha    (unsigned char c);
bool            dt_char_is_alnum    (unsigned char c);

unsigned char   dt_char_to_upper    (unsigned char c);
unsigned char   dt_char_to_lower    (unsigned char c);

size_t          dt_char_span        (const unsigned char *src, size_t len, unsigned char mask);
size_t          dt_char_span_until  (const unsigned char *src, size_t len, unsigned char mask);

size_t          dt_char_skip        (const unsigned char **src, size_t len, unsigned char mask);
size_t          dt_char_skip_until  (const unsigned char **src, size_t len, unsigned char mask);

size_t          dt_char_span_digit  (const unsigned char *src, size_t len);
size_t          dt_char_span_alpha  (const unsigned char *src, size_t len);
size_t          dt_char_span_alnum  (const unsigned char *src, size_t len);

#ifdef __cplusplus
}
#endif
#endif
