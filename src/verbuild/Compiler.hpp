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
#define COMPILER_GNU        0x01000000  /* GNU C++ (g++) compiler.          */
#define COMPILER_GCC48      0x01000001  /* GCC 4.8.x.                       */
#define COMPILER_GCC49      0x01000002  /* GCC 4.9.x.                       */
#define COMPILER_GCC51      0x01000004  /* GCC 5.1.x.                       */
#define COMPILER_GCC52      0x01000008  /* GCC 5.2.x.                       */
#define COMPILER_GCC53      0x01000010  /* GCC 5.3.x.                       */
#define COMPILER_GCC54      0x01000020  /* GCC 5.4.x.                       */
#define COMPILER_GCC61      0x01000040  /* GCC 6.1.x.                       */
#define COMPILER_GCC62      0x01000080  /* GCC 6.2.x.                       */

#define COMPILER_INTEL      0x02000000  /* Intel C++ compiler.              */
#define COMPILER_INTEL110   0x02000001  /* Intel C++ Compiler 11.x.         */
#define COMPILER_INTEL120   0x02000002  /* Intel C++ Compiler 12.x.         */
#define COMPILER_INTEL130   0x02000004  /* Intel C++ Compiler 13.x.         */
#define COMPILER_INTEL140   0x02000008  /* Intel C++ Compiler 14.x.         */
#define COMPILER_INTEL150   0x02000010  /* Intel C++ Compiler 15.x.         */
#define COMPILER_INTEL160   0x02000020  /* Intel C++ Compiler 16.x.         */
#define COMPILER_INTEL170   0x02000040  /* Intel C++ Compiler 17.x.         */

#define COMPILER_CLANG      0x04000000  /* Clang C++ compiler.              */
#define COMPILER_CLANG33    0x04000001  /* Clang 3.3.                       */
#define COMPILER_CLANG34    0x04000002  /* Clang 3.4.                       */
#define COMPILER_CLANG35    0x04000004  /* Clang 3.5.                       */
#define COMPILER_CLANG36    0x04000008  /* Clang 3.6.                       */
#define COMPILER_CLANG37    0x04000010  /* Clang 3.7.                       */
#define COMPILER_CLANG38    0x04000020  /* Clang 3.8.                       */
#define COMPILER_CLANG39    0x04000040  /* Clang 3.9.                       */

/* XCode from 4.x utilises the Clang compiler rathe than GCC. */
#define COMPILER_XCODE      COMPILER_CLANG    /* Apple XCode/Clang.         */
#define COMPILER_XCODE50    COMPILER_CLANG33  /* Apple XCode 5.0.x.         */
#define COMPILER_XCODE51    COMPILER_CLANG34  /* Apple XCode 5.1.x.         */
#define COMPILER_XCODE60    COMPILER_CLANG35  /* Apple XCode 6.0.x.         */
#define COMPILER_XCODE63    COMPILER_CLANG36  /* Apple XCode 6.3.x.         */
#define COMPILER_XCODE70    COMPILER_CLANG37  /* Apple XCode 7.0.x.         */
#define COMPILER_XCODE73    COMPILER_CLANG38  /* Apple XCode 7.3.x.         */
#define COMPILER_XCODE80    COMPILER_CLANG39  /* Apple XCode 8.0.x.         */

#define COMPILER_MICROSOFT  0x08000000  /* Microsoft Visual C++ compiler.   */
#define COMPILER_MSVC2012   0x08000001  /* Visual Studio 2012.              */
#define COMPILER_MSVC2013   0x08000002  /* Visual Studio 2013.              */
#define COMPILER_MSVC2015   0x08000004  /* Visual Studio 2015.              */
#define COMPILER_MSVC2017   0x08000008  /* Visual Studio 2017.              */

#define COMPILER_UNKNOWN    0x80000000  /* Unknown or unsupported compiler. */

/*
 * Determine the compiler vendor and version.
 */
#if defined(__clang__)
# if defined(__apple_build_version__)
#  if (__clang_major__ < 5)
#   error "This compiler is too old!"
#  elif (__clang_major == 5) && (__clang_minor__ == 0)
#   define COMPILER COMPILER_XCODE50
#  elif (__clang_major == 5) && (__clang_minor__ >  0)
#   define COMPILER COMPILER_XCODE51
#  elif (__clang_major == 6) && (__clang_minor__ >= 0) && (__clang_minor__ < 3)
#   define COMPILER COMPILER_XCODE60
#  elif (__clang_major == 6) && (__clang_minor__ >= 3)
#   define COMPILER COMPILER_XCODE63
#  elif (__clang_major == 7) && (__clang_minor__ >= 0) && (__clang_minor__ < 3)
#   define COMPILER COMPILER_XCODE70
#  elif (__clang_major == 7) && (__clang_minor__ >= 3)
#   define COMPILER COMPILER_XCODE73
#  elif (__clang_major == 8) && (__clang_minor__ >= 0)
#   define COMPILER COMPILER_XCODE80
#  else
#   define COMPILER COMPILER_XCODE
#  endif
# else
#  if (__clang_major__ < 3)
#   error "This compiler is too old!"
#  elif (__clang_major__ == 3) && (__clang_minor__ < 3)
#   error "This compiler is too old!"
#  elif (__clang_major__ == 3) && (__clang_minor__ == 3)
#   define COMPILER COMPILER_CLANG33
#  elif (__clang_major__ == 3) && (__clang_minor__ == 4)
#   define COMPILER COMPILER_CLANG34
#  elif (__clang_major__ == 3) && (__clang_minor__ == 5)
#   define COMPILER COMPILER_CLANG35
#  elif (__clang_major__ == 3) && (__clang_minor__ == 6)
#   define COMPILER COMPILER_CLANG36
#  elif (__clang_major__ == 3) && (__clang_minor__ == 7)
#   define COMPILER COMPILER_CLANG37
#  elif (__clang_major__ == 3) && (__clang_minor__ == 8)
#   define COMPILER COMPILER_CLANG38
#  elif (__clang_major__ == 3) && (__clang_minor__ == 9)
#   define COMPILER COMPILER_CLANG39
#  else
#   define COMPILER COMPILER_CLANG
#  endif
# endif
#elif defined(__GNUC__)
# if (__GNUC__ < 4)
#  error "This compiler is too old!"
# elif (__GNUC__ == 4) && (__GNUC_MINOR__ <  8)
#  error "This compiler is too old!"
# elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 8)
#  define COMPILER COMPILER_GCC48
# elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 9)
#  define COMPILER COMPILER_GCC49
# elif (__GNUC__ == 5) && (__GNUC_MINOR__ == 1)
#  define COMPILER COMPILER_GCC51
# elif (__GNUC__ == 5) && (__GNUC_MINOR__ == 2)
#  define COMPILER COMPILER_GCC52
# elif (__GNUC__ == 5) && (__GNUC_MINOR__ == 3)
#  define COMPILER COMPILER_GCC53
# elif (__GNUC__ == 5) && (__GNUC_MINOR__ == 4)
#  define COMPILER COMPILER_GCC54
# elif (__GNUC__ == 6) && (__GNUC_MINOR__ == 1)
#  define COMPILER COMPILER_GCC61
# elif (__GNUC__ == 6) && (__GNUC_MINOR__ == 2)
#  define COMPILER COMPILER_GCC62
# else
#  define COMPILER COMPILER_GNU
# endif
#elif defined(__INTEL_COMPILER) || defined(__ICC)
# if (__INTEL_COMPILER < 1100)
#  error "This compiler is too old!"
# elif (__INTEL_COMPILER >= 1100) && (__INTEL_COMPILER < 1200)
#  define COMPILER COMPILER_INTEL110
# elif (__INTEL_COMPILER >= 1200) && (__INTEL_COMPILER < 1300)
#  define COMPILER COMPILER_INTEL120
# elif (__INTEL_COMPILER >= 1300) && (__INTEL_COMPILER < 1400)
#  define COMPILER COMPILER_INTEL130
# elif (__INTEL_COMPILER >= 1400) && (__INTEL_COMPILER < 1500)
#  define COMPILER COMPILER_INTEL140
# elif (__INTEL_COMPILER >= 1500) && (__INTEL_COMPILER < 1600)
#  define COMPILER COMPILER_INTEL150
# elif (__INTEL_COMPILER >= 1600) && (__INTEL_COMPILER < 1700)
#  define COMPILER COMPILER_INTEL160
# elif (__INTEL_COMPILER >= 1700) && (__INTEL_COMPILER < 1800)
#  define COMPILER COMPILER_INTEL170
# else
#  define COMPILER COMPILER_INTEL
# endif
#elif defined(_MSC_VER)
# if (_MSC_VER < 1700)
#  error "This compiler is too old!"
# elif (_MSC_VER >= 1700) && (_MSC_VER < 1800)
#  define COMPILER COMPILER_MSVC2012
# elif (_MSC_VER >= 1800) && (_MSC_VER < 1900)
#  define COMPILER COMPILER_MSVC2013
# elif (_MSC_VER >= 1900) && (_MSC_VER < 1910)
#  define COMPILER COMPILER_MSVC2015
# elif (_MSC_VER >= 1910) && (_MSC_VER < 2000)
#  define COMPILER COMPILER_MSVC2017
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

/**
 * @brief Is the compiler greater than or equal to a specific compiler in a
 *        specific family?
 * @param __f The compiler family, e.g. COMPILER_GNU.
 * @param __c The compiler to check for, e.g. COMPILER_GCC44.
 * @see COMPILER_LT
 */
#define COMPILER_GT(__f,__c) \
  (COMPILER & __f) && (COMPILER >= __c)

/**
 * @brief Is the compiler lesser than or equal to a specific compiler in a
 *        specific family?
 * @param __f The compiler family, e.g. COMPILER_GNU.
 * @param __c The compiler to check for, e.g. COMPILER_GCC44.
 * @see COMPILER_GT
 */
#define COMPILER_LT(__f,__c) \
  (COMPILER & __f) && (COMPILER <  __c)

/*
 * Compiler standards.
 */
#define STANDARD_CXX98    0x00002001    /*!< C++98 - ISO/IEC 14882:1998.    */
#define STANDARD_CXX11    0x00002002    /*!< C++11 - ISO/IEC 14882:2011.    */
#define STANDARD_CXX14    0x00002004    /*!< C++14 - ISO/IEC 14882:2014.    */
#define STANDARD_CXX17    0x00002008    /*!< C++17 - Not published yet.     */

/*
 * Attempt to detect the C/C++ standard being used.
 */
#if defined(__cplusplus)
# if (__cplusplus == 199711L)
#  define CXX_STANDARD    STANDARD_CXX98
# elif (__cplusplus == 201103L)
#  define CXX_STANDARD    STANDARD_CXX11
# elif (__cplusplus == 201402L)
#  define CXX_STANDARD    STANDARD_CXX17
# endif
#else
# error "You cannot compile this with a C compiler!"
#endif

/*
 * Treat Microsoft Visual Studio 2012 and higher as having
 * the ability to handle the C++11 standard.
 */
#if defined(_MSC_VER) && (_MSC_VER >= 1700)
# undef CXX_STANDARD
# if _MSC_VER >= 1910
#  define CXX_STANDARD STANDARD_CXX17
# elif _MSC_VER >= 19000
#  define CXX_STANDARD STANDARD_CXX14
# else
#  define CXX_STANDARD STANDARD_CXX11
# endif
#endif

/**
 * @brief Is the C++ standard equal to a specific C++ standard?
 * @param __s The C++ standard to test against.
 * @see CXX_STANDARD_LT
 * @see CXX_STANDARD_GT
 */
#define CXX_STANDARD_EQ(__s) \
  (CXX_STANDARD &  __s)

/**
 * @brief Is the C++ standard greater than or equal to a specific C++
 *        standard?
 * @param __s The C++ standard to test against.
 * @see CXX_STANDARD_LT
 */
#define CXX_STANDARD_GT(__s) \
  (CXX_STANDARD >= __s)

/**
 * @brief Is the C++ standard greater than or equal to a specific C++
 *        standard?
 * @param __s The C++ standard to test against.
 * @see CXX_STANDARD_GT
 */
#define CXX_STANDARD_LT(__s) \
  (CXX_STANDARD <  __s)

#endif // !_Compiler_hpp_

// Compiler.hpp ends here.
