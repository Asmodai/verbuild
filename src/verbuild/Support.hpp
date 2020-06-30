//
// Support.hpp --- Support utilities.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    28 Nov 2016 12:37:14
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
 * @file Support.hpp
 * @author Paul Ward
 * @brief Support utilities.
 */

#pragma once
#ifndef _Support_hpp_
#define _Support_hpp_

#include "Platform.hpp"
#include "Compiler.hpp"

/*
 * Deal with 'secure CRT' compile-time errors.
 */
#if PLATFORM_EQ(PLATFORM_WINDOWS)
# if !defined(_CRT_SECURE_NO_WARNINGS)
#  define _CRT_SECURE_NO_WARNINGS
# endif
# if !defined(_SCL_SECURE_NO_WARNINGS)
#  define _SCL_SECURE_NO_WARNINGS
# endif
#endif

/*
 *             SD-6: SG10 FEATURE TEST RECOMMENDATIONS
 *               Coming soon to a compiler near you!
 *
 * This is one hell of a mess, nothing is backward compatible with
 * this, and some compilers will no doubt not bother with any of these
 * for a considerable period of time.
 *
 *
 *                            RATIONALE
 *
 * In order for us to make (limited) use of these macros -- until
 * their usage is widespread and all legacy compilers have been thrown
 * away (hahaha) -- we should define some "feature test" feature
 * tests.
 */

/**
 * @def __have_sd6_tests__
 * @brief Does the compiler support the feature test recommendations
 *        from SD-6?
 *
 * If defined, then the tests from N4200 - SD-6: SG10 Feature Test
 * Recommendations are available for use.
 */
#if defined(__has_include) &&                   \
    defined(__has_cpp_attribute)
# define __have_sd6_tests__
#endif

/**
 * @def __have_header_tests__
 * @brief Does the compiler support testing for header files?
 *
 * If defined, then @em at @em least @c __has_include and
 * @c __has_include_next are supported by the compiler.
 *
 * Note that this is @b not the same as GNU's @c #include_next.
 */
#if defined(__has_include) &&                   \
    defined(__has_include_next)
# define __has_header_tests__ 1
#endif

/**
 * @def __have_attribute_tests__
 * @brief Does the compiler support testing for attributes?
 *
 * If defined, then @em at @em least @c __has_attribute is supported
 * by the compiler.
 *
 * Clang provides @c __has_declspec_attribute for testing Microsoft
 * Visual C++ attributes (i.e. noreturn), but I cannot see any
 * evidence that suggests this will be adopted by other compiler
 * vendors, so we simply ignore that with this test.
 *
 * Also be aware that @c __has_cpp_attribute is part of SD-6, so
 */
#if defined(__has_attribute)
# define __has_attribute_tests__ 1
#endif

/**
 * @def __have_feature_tests__
 * @brief Does the compiler support extended testing?
 *
 * If defined, then at least @em at @em least @c __has_builtin and
 * @c __has_feature are supported by the compiler.
 *
 * These are mostly Clang extensions and probably will not make it to
 * other compilers.
 */
#if defined(__has_builtin) &&                   \
    defined(__has_feature)
# define __has_feature_tests__ 1
#endif

/**
 * @def __has_include
 * @brief Determines whether the given include file is present.
 * @param __hdr The header for which to test.
 * @returns 1 if the header is available for use; otherwise 0 is
 *          returned.
 * @note On compilers that do not support this macro, the result is
 *       @b always 0.
 */
#if !defined(__has_include)
# define __has_include(__hdr) 0
#endif

/**
 * @def __has_include_next
 * @brief Determines whether the given include file is present.
 * @param __hdr The header for which to test.
 * @returns 1 if the header is available for use; otherwise 0 is
 *          returned.
 * @note On compilers that do not support this macro, the result is
 *       @b always 0.
 *
 * This is similar to @c __has_include except that it looks for the
 * @b second instance of the given file.
 */
#if !defined(__has_include_next)
# define __has_include_next(__hdr) 0
#endif

/**
 * @def __has_builtin
 * @brief Determines whether the given identifier is a builtin function.
 * @param __ident The identifier to test.
 * @returns 1 if the builtin is supported; otherwise 0 is returned.
 * @note On compilers that do not support this macro, the result is
 *       @b always 0.
 */
#if !defined(__has_builtin)
# define __has_builtin(__ident) 0
#endif

/**
 * @def __has_feature
 * @brief Determine whether a C++ feature is available.
 * @param __feature The feature for which to test.
 * @returns 1 if the feature is available for use; otherwise 0 is
 *          returned.
 * @note On compilers that do not support this macro, it simply
 *       expands to the feature test so the preprocessor can at least
 *       try to test for a feature.
 */
#if !defined(__has_feature)
# define __has_feature(__feature) __feature
#endif

/**
 * @def __has_cpp_attribute
 * @brief Determine whether a C++11-style attribute is available.
 * @param __attrib The attribute for which to test.
 * @returns 1 if the attribute is available; otherwise 0 is returned.
 * @note On compilers that do not support this macro, the result is
 *       @b always 0.
 */
#if !defined(__has_cpp_attribute)
# define __has_cpp_attribute(__attrib) 0
#endif

/**
 * @def __has_cpp_attribute
 * @brief Determine whether a GNU-style attribute is available.
 * @param __attrib The attribute for which to test.
 * @returns 1 if the attribute is available; otherwise 0 is returned.
 * @note On compilers that do not support this macro, the result is
 *       @b always 0.
 */
#if !defined(__has_attribute)
# define __has_attribute(__attrib) 0
#endif

/**
 * @def __has_declspec_attribute
 * @brief Determine whether a Microsoft-style __declspec attribute is
 *        available.
 * @param __attrib The attribute for which to test.
 * @returns 1 if the attribute is available; otherwise 0 is returned.
 * @note On compilers that do not support this macro, the result is
 *       @b always 0.
 */
#if !defined(__has_declspec_attribute)
# define __has_declspec_attribute(__attrib) 0
#endif

/**
 * @def __has_extension
 * @brief Determine whether a language extension or feature is
 *        available.
 * @note On compilers that do not support this macro, it simply
 *       expands to use the @c __has_feature test.
 */
#if !defined(__has_extension)
# define __has_extension __has_feature
#endif

/**
 * @def BITS_64
 * @brief The target has 64-bit machine words.
 *
 * @def BITS_32
 * @brief The target has 32-bit machine words.
 *
 * @def __WORDSIZE
 * @brief Defined for compatability with systems that do not use the
 *        __WORDSIZE preprocessor macro.
 */
#if defined(__WORDSIZE)
# if __WORDSIZE == 64
#  define BITS_64
# else
#  define BITS_32
# endif
#elif PLATFORM_EQ(PLATFORM_WINDOWS)
# if defined(_WIN64)
#  define BITS_64
#  define __WORDSIZE 64
# else
#  define BITS_32
#  define __WORDSIZE 32
# endif
#else
# define BITS_32
# define __WORDSIZE  32
#endif

/*
 * Bring in endianess.
 */
#if PLATFORM_EQ(PLATFORM_UNIX)
# include <endian.h>
#else
# define __BIG_ENDIAN    3412
# define __LITTLE_ENDIAN 1234
#endif

/**
 * @def __BYTE_ORDER
 * @brief The endianess of the platform.
 * @note Special endianess like @c __PDP_ENDIAN are not supported.
 *
 * May contain either @c __BIG_ENDIAN or @c __LITTLE_ENDIAN.
 */
#if PLATFORM_EQ(PLATFORM_WINDOWS)
# define __BYTE_ORDER __LITTLE_ENDIAN
#elif defined(__BIG_ENDIAN__)
# define __BYTE_ORDER __BIG_ENDIAN
#elif defined(__LITTLE_ENDIAN__)
# define __BYTE_ORDER __LITTLE_ENDIAN
#elif defined(__BYTE_ORDER__)
# if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#  define __BYTE_ORDER __BIG_ENDIAN
# elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#  define __BYTE_ORDER __LITTLE_ENDIAN
# endif
#else
# error Unable to determine endianess of this platform.
#endif

/*
 * Standard integer types that may be missing.
 */
#if __has_include(<cstdint>)
# include <cstdint>
#else
# error No cstdint available
#endif

/*
 * Visual Studio defines _DEBUG when the Debug configuration is
 * active, but Unix users traditionally use -DDEBUG.  If _DEBUG is
 * defined but DEBUG isn't, then define DEBUG.
 */
#if defined(_DEBUG) && !defined(DEBUG)
# define DEBUG 1
#endif

/*
 * Likewise, Windows-specific code will most likely just use _DBEUG, so
 * if DEBUG is defined but _DEBUG isn't, then define _DEBUG.
 */
#if defined(DEBUG) && !defined(_DEBUG)
# define _DEBUG DEBUG
#endif

/**
 * @def __noreturn
 * @brief Inform the compiler that this function will not return.
 * @note This only works with compilers that support this type of compiler
 *       hint.
 */

#if __has_cpp_attribute(noreturn)
# define NORETURN [[noreturn]] void
#elif __has_attribute(noreturn)
# define NORETURN void __attribute__((noreturn))
#else
# define NORETURN void
#endif

/**
 * @def __unused_variable
 * @brief Inform the compiler that a variable is unused.
 */
#if COMPILER_EQ(COMPILER_GNU) || COMPILER_EQ(CLANG)
# define UNUSED_VARIABLE(__v) \
  __v __attribute__((unused))
#elif COMPILER_EQ(COMPILER_MICROSOFT)
# define UNUSED_VARIABLE(__v) \
  __pragma(warning(suppress: 4100 4101)) __v
#else
# define UNUSED_VARIABLE(__v) __v
#endif

/**
 * @def __PRETTY_FUNCTION__
 * @brief Define the @em __PRETTY_FUNCTION__ macro on platforms that lack their
 *        definition.
 *
 * @em __PRETTY_FUNCTION__ is defined as a GNU extension which, when used,
 * prints out the function in a nice pretty way; that is, `void a::thing(int)`
 * instead of just `sub`.
 *
 * Microsoft make this available via the @em __FUNCSIG__ macro.  Not sure
 * about other compilers right now.  Hopefully clang does things the GCC way.
 */
#if COMPILER_EQ(COMPILER_MICROSOFT)
# if !defined(__PRETTY_FUNCTION__)
// Well, the above is all good and all, but man, __FUNCSIG__ outputs waaaay
// too much stuff.  I've decided I don't care.

#  define __PRETTY_FUNCTION__ __func__
# endif
#endif

/**
 * @def FORCE_INLINE
 * @brief A compiler-specific way of forcing something to be inline.
 * @note This probably isn't what you think it is, as some compilers already
 *       have ways to determine whether something should be inline or not.
 */
#if COMPILER_EQ(COMPILER_MICROSOFT)
# define FORCE_INLINE __forceinline
#elif COMPILER_EQ(COMPILER_GNU)
# define FORCE_INLINE inline __attribute__((always_inline))
#else
# define FORCE_INLINE __inline
#endif

/**
 * @def QUOTE_INPLACE
 * @brief Quote a macro variable in place.
 */
#define QUOTE_INPLACE(x) # x

/**
 * @def QUOTE
 * @brief Quote a variable in a macro.
 */
#define QUOTE(x) QUOTE_INPLACE(x)

/**
 * @def WARN
 * @brief Generate a compiler warning.
 */
#define WARN(x) message(__FILE__ "(" QUOTE(__LINE__) ") :" x "\n")

/**
 * @def OVERRIDE
 * @brief Macro for the C++11 @em override specifier.
 */
#define OVERRIDE override


/**
 * @def DEPRECATED
 * @brief Mark a function as deprecated.
 */
#define DEPRICATED [[deprecated]]

/**
 * @def DEPRECATED_EX
 * @brief Mark a function as deprecated, issuing a compiler warning if used.
 */
#define DEPRICATED_EX(__msg) [[deprecated(__msg)]]

/**
 * @def _EXPORT
 * @brief Attribute to mark a function as exported.
 *
 * @def _PRIVATE
 * @brief Attribute to mark a function as private.
 */
#if COMPILER_EQ(COMPILER_GNU) || COMPILER_EQ(COMPILER_CLANG)
# define _EXPORT  __attribute__((visibility("default")))
# define _PRIVATE __attribute__((visibility("hidden")))
#else
# define _EXPORT
# define _PRIVATE
#endif

/**
 * @def DECL_MALLOC
 * @brief Attribute to mark a function as having aliases.
 */
#if COMPILER_EQ(COMPILER_MICROSOFT)
# define DECL_MALLOC __declspec(restrict) __declspec(noalias)
#else
# define DECL_MALLOC __attribute__((malloc))
#endif

/*
 * Redefine `stricmp` to `strcasecmp` on platforms where doing so makes
 * more sense.
 */
#if PLATFORM_EQ(PLATFORM_LINUX) || PLATFORM_EQ(PLATFORM_MACOSX)
# define stricmp strcasecmp
#endif

/*
 * Check if we can use Unicode.
 */
#if PLATFORM_EQ(PLATFORM_LINUX) || PLATFORM_EQ(PLATFORM_MACOSX)
# define UNICODE_SUPPORT 1
#elif PLATFORM_EQ(PLATFORM_WINDOWS)
# if defined(UNICODE) || defined(_UNICODE)
#  define UNICODE_SUPPORT 1
# endif
#endif

/*
 * SIMD stack allignment for the Intel compiler.
 */
#if COMPILER_EQ(COMPILER_INTEL)
# define SIMD_ALIGN_STACK     _alloca(16)
# define SIMD_ALIGN_ATTRIBUTE
#endif

#endif // !_Support_hpp_

// Support.hpp ends here.
