//
// Enums.hpp --- Enums.
//
// Copyright (c) 2013 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Saturday Jun  1, 2013 04:19:25 asmodai>
// Revision:   5
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    01 Jun 2013 03:57:56
// Keywords:   
// URL:        not distributed yet
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
// along with this program; if not, see  <http://www.gnu.org/licenses/>.
//
// }}}
// {{{ Commentary:

// }}}

#ifndef __Enums_hpp__
#define __Enums_hpp__

/**
 * @file Enums.hpp
 * @author Paul Ward
 * @brief Various enums.
 */

#include <QtCore/QFlags>

/**
 * @brief Build number generation type.
 *
 * This controls which method is used to build the build number
 * component.
 */
enum BuildType {
  BuildByMonths,                //!< Use month difference.
  BuildByYears,                 //!< Use month and day.
  BuildByDate,                  //!< Encode date in ISO 8601 format.
  BuildSimple                   //!< Simply increment the number.
};
Q_DECLARE_FLAGS(BuildTypes, BuildType)

/**
 * @enum Increment
 * @brief Incrementation types.
 *
 * @var IncrementMajor
 * @brief Increment the major version number.
 *
 * @var IncrementMinor
 * @brief Increment the minor version number.
 *
 * @var IncrementBuild
 * @brief Increment the build number.
 *
 * @var IncrementPatch
 * @brief Increment the patch number.
 *
 * @var IncrementBuildAndPatch
 * @brief Increment both the build and patch numbers
 *
 * @var IncrementMinorAndBuild
 * @brief Increment both the minor and build numbers.
 *
 * @var IncrementMinorBuildAndPatch
 * @brief Increment the minor, build, and patch numbers.
 */
enum Increment {
  IncrementMajor = 0x01,
  IncrementMinor = 0x02,
  IncrementBuild = 0x04,
  IncrementPatch = 0x08,
  
  IncrementBuildAndPatch = IncrementBuild | IncrementPatch,
  IncrementMinorAndBuild = IncrementMinor | IncrementBuild,
  IncrementMinorBuildAndPatch = IncrementMinorAndBuild | IncrementPatch
};
Q_DECLARE_FLAGS(Increments, Increment)

#endif // !__Enums_hpp__

// Enums.hpp ends here
