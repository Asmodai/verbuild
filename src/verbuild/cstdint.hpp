//
// cstdint.hpp --- `cstdint' shim.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    28 Nov 2016 12:39:20
//
// {{{ License:
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//
// }}}
// {{{ Commentary:

// }}}

/**
 * @file cstdint.hpp
 * @author Paul Ward
 * @brief `cstdint' shim.
 */

#pragma once
#ifndef _cstdint_hpp_
#define _cstdint_hpp_

namespace std
{

  /* Exact types. */
  typedef signed char            int8_t;
  typedef unsigned char          uint8_t;
  typedef short int              int16_t;
  typedef unsigned short int     uint16_t;
  typedef int                    int32_t;
  typedef unsigned int           uint32_t;
#if __WORDSIZE == 64
  typedef long int               int64_t;
  typedef unsigned long int      uint64_t;
#else
  typedef long long int          int64_t;
  typedef unsigned long long int uint64_t;
#endif

  /* Small types. */
  typedef signed char            int_least8_t;
  typedef unsigned char          uint_least8_t;
  typedef short int              int_least16_t;
  typedef unsigned short int     uint_least16_t;
  typedef int                    int_least32_t;
  typedef unsigned int           uint_least32_t;
#if __WORDSIZE == 64
  typedef long int               int_least64_t;
  typedef unsigned long int      uint_least64_t;
#else
  typedef long long int          int_least64_t;
  typedef unsigned long long int uint_least64_t;
#endif

  /* Fast types. */
  typedef signed char            int_fast8_t;
  typedef unsigned char          uint_fast8_t;
#if __WORDSIZE == 64
  typedef long int               int_fast16_t;
  typedef unsigned long int      uint_fast16_t;
  typedef long int               int_fast32_t;
  typedef long int               int_fast64_t;
#else
  typedef int                    int_fast16_t;
  typedef int                    int_fast32_t;
  typedef long long int          int_fast64_t;
  typedef unsigned long long int uint_fast64_t;
#endif

  /* Pointer types. */
#if __WORDSIZE == 64
  typedef long int          intptr_t;
  typedef unsigned long int uintptr_t;
#else
  typedef int               intptr_t;
  typedef unsigned int      intptr_t;
#endif

  /* Largest integral types. */
#if __WORDSIZE == 64
  typedef long int          intmax_t;
  typedef unsigned long int uintmax_t;
#else
  typedef int               intmax_t;
  typedef unsigned int      uintmax_t;
#endif

  /* Macros. */
#if __WORDSIZE == 64
# define __INT64_C(c)  c ## L
# define __UINT64_C(c) c ## UL
#else
# define __INT64_C(c)  c ## LL
# define __UINT64_C(c) c ## ULL
#endif

  /* Integral lower limits. */
#define INT8_MIN     (-128)
#define INT16_MIN    (-32767 - 1)
#define INT32_MIN    (-2147483647 - 1)
#define INT64_MIN    (-__INT64_C(9223372036854775807) - 1)

  /* Integral upper limits. */
#define INT8_MAX     (127)
#define UINT8_MAX    (255)
#define INT16_MAX    (32767)
#define UINT16_MAX   (65535)
#define INT32_MAX    (2147483647)
#define UINT32_MAX   (4294967295U)
#define INT64_MAX    (__INT64_C(9223372036854775807))
#define UINT64_MAX   (__UINT64_C(18446744073709551615))

  /* Minimum of integrals that have a minimum size. */
#define INT_LEAST8_MIN    (-128)
#define INT_LEAST16_MIN   (-32767 - 1)
#define INT_LEAST32_MIN   (-2147483647 - 1)
#define INT_LEAST64_MIN   (-__INT64_C(9223372036854775807) - 1)

  /* Maximum of integrals that have a minimum size. */
#define INT_LEAST8_MAX    (127)
#define UINT_LEAST8_MAX   (255)
#define INT_LEAST16_MAX   (32767)
#define UINT_LEAST16_MAX  (65535)
#define INT_LEAST32_MAX   (2147483647)
#define UINT_LEAST32_MAX  (4294967295U)
#define INT_LEAST64_MAX   (__INT64_C(9223372036854775807))
#define UINT_LEAST64_MAX  (__UINT64_C(18446744073709551615))

  /* Minimum of fast integral types that have a minimum size.  */
#define INT_FAST8_MIN    (-128)
#if __WORDSIZE == 64
# define INT_FAST16_MIN  (-9223372036854775807L - 1)
# define INT_FAST32_MIN  (-9223372036854775807L - 1)
#else
# define INT_FAST16_MIN  (-2147483647 - 1)
# define INT_FAST32_MIN  (-2147483647 - 1)
#endif
#define INT_FAST64_MIN   (-__INT64_C(9223372036854775807) - 1)

  /* Maximum of fast integral types that have a minimum size.  */
#define INT_FAST8_MAX     (127)
#define UINT_FAST8_MAX    (255)
#if __WORDSIZE == 64
# define INT_FAST16_MAX   (9223372036854775807L)
# define UINT_FAST16_MAX  (18446744073709551615UL)
# define INT_FAST32_MAX   (9223372036854775807L)
# define UINT_FAST32_MAX  (18446744073709551615UL)
#else
# define INT_FAST16_MAX   (2147483647)
# define UINT_FAST16_MAX  (4294967295U)
# define INT_FAST32_MAX   (2147483647)
# define UINT_FAST32_MAX  (4294967295U)
#endif
#define INT_FAST64_MAX    (__INT64_C(9223372036854775807))
#define UINT_FAST64_MAX   (__UINT64_C(18446744073709551615))

  /* Values to test for integral types holding `void *' pointer.  */
#if __WORDSIZE == 64
# define INTPTR_MIN   (-9223372036854775807L-1)
# define INTPTR_MAX   (9223372036854775807L)
# define UINTPTR_MAX  (18446744073709551615UL)
#else
# define INTPTR_MIN   (-2147483647-1)
# define INTPTR_MAX   (2147483647)
# define UINTPTR_MAX  (4294967295U)
#endif

  /* Minimum for largest signed integral type.  */
#define INTMAX_MIN  (-__INT64_C(9223372036854775807)-1)

  /* Maximum for largest unsigned integral type.  */
#define INTMAX_MAX  (__INT64_C(9223372036854775807))

  /* Maximum for largest unsigned integral type.  */
#define UINTMAX_MAX  (__UINT64_C(18446744073709551615))

  /* Limits of `ptrdiff_t' type.  */
#if __WORDSIZE == 64
# define PTRDIFF_MIN  (-9223372036854775807L-1)
# define PTRDIFF_MAX  (9223372036854775807L)
#else
# define PTRDIFF_MIN  (-2147483647-1)
# define PTRDIFF_MAX  (2147483647)
#endif

  /* Limits of `sig_atomic_t'.  */
#define SIG_ATOMIC_MIN  (-2147483647-1)
#define SIG_ATOMIC_MAX  (2147483647)

  /* Limit of `size_t' type.  */
#if __WORDSIZE == 64
# define SIZE_MAX  (18446744073709551615UL)
#else
# define SIZE_MAX  (4294967295U)
#endif

  /*
  * Some platforms this code works on won't have wchar.h
  */
#if defined(PLATFORM_NEXT)
# define __WCHAR_MIN   0
# define __WCHAR_MAX   UINT16_MAX
#endif

  /* Limits of `wchar_t'.  */
#ifndef WCHAR_MIN
# define WCHAR_MIN  __WCHAR_MIN
# define WCHAR_MAX  __WCHAR_MAX
#endif

  /* Limits of `wint_t'.  */
#define WINT_MIN  (0u)
#define WINT_MAX  (4294967295u)

  /* More macros. */
#define INT8_C(c)      c
#define INT16_C(c)     c
#define INT32_C(c)     c
#define UINT8_C(c)     c
#define UINT16_C(c)    c
#define UINT32_C(c)    c ## U
#if __WORDSIZE == 64
# define INT64_C(c)    c ## L
# define UINT64_C(c)   c ## UL
#else
# define INT64_C(c)    c ## LL
# define UINT64_C(c)   c ## ULL
#endif

  /* Maximal type.  */
#if __WORDSIZE == 64
# define INTMAX_C(c)   c ## L
# define UINTMAX_C(c)  c ## UL
#else
# define INTMAX_C(c)   c ## LL
# define UINTMAX_C(c)  c ## ULL
#endif

}

#endif // !_cstdint_hpp_

// cstdint.hpp ends here.
