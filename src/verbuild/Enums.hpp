//
// Enums.hpp --- Various enums.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    01 Jun 2013 03:57:56
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
 * @file Enums.hpp
 * @author Paul Ward
 * @brief Various enums.
 */

#pragma once
#ifndef _Enums_hpp_
#define _Enums_hpp_

#include <ostream>

#include "bitmask.hpp"
#include "Utils.hpp"

enum class IncrementType {
  ByMonths,
  ByYears,
  ByDate,
  Simple,
};

enum class IncrementMode : unsigned char {
  None  = 0x0,
  Major = 0x01,
  Minor = 0x02,
  Build = 0x04,
  Patch = 0x08,
  All   = 0xFF,

  BuildAndPatch      = Build | Patch,
  MinorAndBuild      = Minor | Build,
  MinorBuildAndPatch = MinorAndBuild | Patch,

  First = None,
  Last  = All
};
ENABLE_BITMASK_OPS(IncrementMode)

enum class OutputGroups : unsigned char {
  None    = 0x0,
  Basic   = 0x01,
  Struct  = 0x02,
  Doxygen = 0x04,
  All     = 0xFF
};
ENABLE_BITMASK_OPS(OutputGroups);

std::ostream &operator<<(std::ostream &, const IncrementType &);
std::ostream &operator<<(std::ostream &, const IncrementMode &);
std::ostream &operator<<(std::ostream &, const OutputGroups &);

#endif // !_Enums_hpp_

// Enums.hpp ends here.
