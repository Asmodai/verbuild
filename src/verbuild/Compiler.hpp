//
// Compiler.hpp --- Compiler detection
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    28 Nov 2016 11:57:56
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
 * @file Compiler.hpp
 * @author Paul Ward
 * @brief Compiler detection
 */

#pragma once
#ifndef _Compiler_hpp_
#define _Compiler_hpp_

/*
* Compiler versions.
*/
#define COMPILER_GNU        1                 /* GNU C++ (g++) compiler.          */
#define COMPILER_INTEL      2                 /* Intel C++ compiler.              */
#define COMPILER_CLANG      3                 /* Clang C++ compiler.              */
#define COMPILER_XCODE      COMPILER_CLANG    /* Apple XCode/Clang.         */
#define COMPILER_MICROSOFT  4                 /* Microsoft Visual C++ compiler.   */
#define COMPILER_UNKNOWN    5                 /* Unknown or unsupported compiler. */

/*
 * Determine the compiler vendor and version.
 */
#if defined(__clang__)
# if defined(__apple_build_version__)
#  if (__clang_major__ < 5)
#   error This compiler is too old
#  else
#   define COMPILER COMPILER_XCODE
#  endif
# else
#  if (__clang_major__ < 4)
#   error This compiler is too old
#  else
#   define COMPILER COMPILER_CLANG
#  endif
# endif
#elif defined(__GNUC__)
# if (__GNUC__ < 7)
#  error This compiler is too old
# else
#  define COMPILER COMPILER_GNU
# endif
#elif defined(__INTEL_COMPILER) || defined(__ICC)
# if (__INTEL_COMPILER < 1901)
#  error This compiler is too old
# else
#  define COMPILER COMPILER_INTEL
# endif
#elif defined(_MSC_VER)
# if (_MSC_VER < 1926)
#  error This compiler is too old
# else
#  define COMPILER COMPILER_MICROSOFT
# endif
#elif
# define COMPILER COMPILER_UNKNOWN
#endif

/**
 * @brief Is the compiler equal to a family or specific compiler?
 * @param __c The compiler to check for, e.g. COMPILER_MSVC2002.
 * @see COMPILER_GT
 * @see COMPILER_LT
 */
#define COMPILER_EQ(__c) \
  (COMPILER & __c)

#endif // !_Compiler_hpp_

// Compiler.hpp ends here.
