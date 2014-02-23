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
#ifndef __DT_CONFIG_H__
#define __DT_CONFIG_H__

#if !defined(_MSC_VER)
#  include <stdbool.h>
#endif

#if !defined(__cplusplus) && !defined(__bool_true_false_are_defined)
   typedef char  _Bool;
#  define  bool  _Bool
#  define  true  1
#  define  false 0
#  define  __bool_true_false_are_defined 1
#endif

/* Chronological Julian Date, January 1, 4713 BC, Monday
#define DT_EPOCH_OFFSET 1721425
*/

/* Network Time Protocol (NTP), January 1, 1900, Monday
#define DT_EPOCH_OFFSET -693596
*/

/* Unix, January 1, 1970, Thursday
#define DT_EPOCH_OFFSET -719163
*/

/* Rata Die, January 1, 0001, Monday (as Day 1) */
#define DT_EPOCH_OFFSET 0

#ifdef __cplusplus
extern "C" {
#endif

typedef int dt_t;

#ifdef __cplusplus
}
#endif
#endif
