//
// Platform.hpp --- Platform detection.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    28 Nov 2016 12:33:49
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
 * @file Platform.hpp
 * @author Paul Ward
 * @brief Platform detection.
 */

#pragma once
#ifndef _Platform_hpp_
#define _Platform_hpp_

#define PLATFORM_WINDOWS   1   /*!< Microsoft Windows. */
#define PLATFORM_UNIX      2   /*!< Unix or Unix-like. */
#define PLATFORM_BSD       3   /*!< BSD. */
#define PLATFORM_MACOSX    5   /*!< Apple MacOS X. */
#define PLATFORM_LINUX     6   /*!< GNU/Linux. */

/*
 * Detect the operating system.
 */
#if defined(__gnu_linux__) || defined(__linux__) || \
  defined(__linux) || defined(linux)
# define PLATFORM          PLATFORM_LINUX
# define PLATFORM_NAME     "GNU/Linux"
# define PLATFORM_FEATURE  "gnulinux"
#elif defined(_WIN32) || defined(_WIN64)
# define PLATFORM          PLATFORM_WINDOWS
# define PLATFORM_NAME     "Microsoft Windows"
# define PLATFORM_FEATURE  "windows"
#elif defined(__APPLE__) && defined(__MACH__)
# define PLATFORM          PLATFORM_MACOSX
# define PLATFORM_NAME     "Apple OS X"
# define PLATFORM_FEATURE  "macosx"
#endif

/**
 * @brief Is the platform equal to a specific platform?
 * @param __p The platform to test against.
 * @see PLATFORM_LT
 * @see PLATFORM_GT
 */
#define PLATFORM_EQ(__p)                        \
  (PLATFORM & __p)

#endif // !_Platform_hpp_

// Platform.hpp ends here.
