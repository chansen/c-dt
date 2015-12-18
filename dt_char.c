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
#include "dt_char.h"

enum {
    HSPACE = DT_CHAR_HSPACE,
    VSPACE = DT_CHAR_VSPACE,
    PUNCT  = DT_CHAR_PUNCT,
    DIGIT  = DT_CHAR_DIGIT,
    UPPER  = DT_CHAR_UPPER,
    LOWER  = DT_CHAR_LOWER,
    OTHER  = DT_CHAR_OTHER,
};

static const unsigned char dt_char_table[0x100] = {
 /* 00 NUL      01 SOH      02 STX      03 ETX    */
 /* 04 EOT      05 ENQ      06 ACK      07 BEL    */
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
 /* 08 BS       09 HT       0A NL       0B VT     */
 /* 0C NP       0D CR       0E SO       0F SI     */
    OTHER,      HSPACE,     VSPACE,     OTHER,   
    OTHER,      VSPACE,     OTHER,      OTHER,   
 /* 10 DLE      11 DC1      12 DC2      13 DC3    */
 /* 14 DC4      15 NAK      16 SYN      17 ETB    */
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
 /* 18 CAN      19 EM       1A SUB      1B ESC    */
 /* 1C FS       1D GS       1E RS       1F US     */
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
 /* 20 SP       21  !       22  "       23  #     */
 /* 24  $       25  %       26  &       27  '     */
    HSPACE,     PUNCT,      PUNCT,      PUNCT,   
    PUNCT,      PUNCT,      PUNCT,      PUNCT,   
 /* 28  (       29  )       2A  *       2B  +     */
 /* 2C  ,       2D  -       2E  .       2F  /     */
    PUNCT,      PUNCT,      PUNCT,      PUNCT,   
    PUNCT,      PUNCT,      PUNCT,      PUNCT,   
 /* 30  0       31  1       32  2       33  3     */
 /* 34  4       35  5       36  6       37  7     */
    DIGIT,      DIGIT,      DIGIT,      DIGIT,   
    DIGIT,      DIGIT,      DIGIT,      DIGIT,   
 /* 38  8       39  9       3A  :       3B  ;     */
 /* 3C  <       3D  =       3E  >       3F  ?     */
    DIGIT,      DIGIT,      PUNCT,      PUNCT,   
    PUNCT,      PUNCT,      PUNCT,      PUNCT,   
 /* 40  @       41  A       42  B       43  C     */
 /* 44  D       45  E       46  F       47  G     */
    PUNCT,      UPPER,      UPPER,      UPPER,   
    UPPER,      UPPER,      UPPER,      UPPER,   
 /* 48  H       49  I       4A  J       4B  K     */
 /* 4C  L       4D  M       4E  N       4F  O     */
    UPPER,      UPPER,      UPPER,      UPPER,   
    UPPER,      UPPER,      UPPER,      UPPER,   
 /* 50  P       51  Q       52  R       53  S     */
 /* 54  T       55  U       56  V       57  W     */
    UPPER,      UPPER,      UPPER,      UPPER,   
    UPPER,      UPPER,      UPPER,      UPPER,   
 /* 58  X       59  Y       5A  Z       5B  [     */
 /* 5C  \       5D  ]       5E  ^       5F  _     */
    UPPER,      UPPER,      UPPER,      PUNCT,   
    PUNCT,      PUNCT,      PUNCT,      PUNCT,   
 /* 60  `       61  a       62  b       63  c     */
 /* 64  d       65  e       66  f       67  g     */
    PUNCT,      LOWER,      LOWER,      LOWER,   
    LOWER,      LOWER,      LOWER,      LOWER,   
 /* 68  h       69  i       6A  j       6B  k     */
 /* 6C  l       6D  m       6E  n       6F  o     */
    LOWER,      LOWER,      LOWER,      LOWER,   
    LOWER,      LOWER,      LOWER,      LOWER,   
 /* 70  p       71  q       72  r       73  s     */
 /* 74  t       75  u       76  v       77  w     */
    LOWER,      LOWER,      LOWER,      LOWER,   
    LOWER,      LOWER,      LOWER,      LOWER,   
 /* 78  x       79  y       7A  z       7B  {     */
 /* 7C  |       7D  }       7E  ~       7F DEL    */
    LOWER,      LOWER,      LOWER,      PUNCT,   
    PUNCT,      PUNCT,      PUNCT,      OTHER,   
 /* 80 .. FF                                      */
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,   
    OTHER,      OTHER,      OTHER,      OTHER,
};

bool
dt_char_is_of(unsigned char c, unsigned char mask) {
    return (dt_char_table[c] & mask) != 0;
}

bool
dt_char_is_space(unsigned char c) {
    return (dt_char_table[c] & DT_CHAR_SPACE) != 0;
}

bool
dt_char_is_blank(unsigned char c) {
    return (dt_char_table[c] & DT_CHAR_BLANK) != 0;
}

bool
dt_char_is_punct(unsigned char c) {
    return (dt_char_table[c] & DT_CHAR_PUNCT) != 0;
}

bool
dt_char_is_digit(unsigned char c) {
    return (dt_char_table[c] & DT_CHAR_DIGIT) != 0;
}

bool
dt_char_is_lower(unsigned char c) {
    return (dt_char_table[c] & DT_CHAR_LOWER) != 0;
}

bool
dt_char_is_upper(unsigned char c) {
    return (dt_char_table[c] & DT_CHAR_UPPER) != 0;
}

bool
dt_char_is_alpha(unsigned char c) {
    return (dt_char_table[c] & DT_CHAR_ALPHA) != 0;
}

bool
dt_char_is_alnum(unsigned char c) {
    return (dt_char_table[c] & DT_CHAR_ALNUM) != 0;
}

unsigned char
dt_char_to_upper(unsigned char c) {
    if (dt_char_is_lower(c))
        c &= 0xDF;
    return c;
}

unsigned char
dt_char_to_lower(unsigned char c) {
    if (dt_char_is_upper(c))
        c |= 0x20;
    return c;
}

size_t
dt_char_span(const unsigned char *src, size_t len, unsigned char mask) {
    size_t n;

    for (n = 0; n < len; n++) {
        const unsigned char c = src[n];
        if ((dt_char_table[c] & mask) != 0)
            break;
    }
    return n;
}

size_t
dt_char_skip(const unsigned char **src, size_t len, unsigned char mask) {
    *src += len = dt_char_span(*src, len, mask);
    return len;
}

size_t
dt_char_span_until(const unsigned char *src, size_t len, unsigned char mask) {
    size_t n;

    for (n = 0; n < len; n++) {
        const unsigned char c = src[n];
        if ((dt_char_table[c] & mask) == 0)
            break;
    }
    return n;
}

size_t
dt_char_skip_until(const unsigned char **src, size_t len, unsigned char mask) {
    *src += len = dt_char_span_until(*src, len, mask);
    return len;
}

size_t
dt_char_span_digit(const unsigned char *src, size_t len) {
    return dt_char_span(src, len, DT_CHAR_DIGIT);
}

size_t
dt_char_span_alpha(const unsigned char *src, size_t len) {
    return dt_char_span(src, len, DT_CHAR_ALPHA);
}

size_t
dt_char_span_alnum(const unsigned char *src, size_t len) {
    return dt_char_span(src, len, DT_CHAR_ALNUM);
}
