//
// Enums.cpp --- Various enums.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    22 Nov 2017 00:02:25
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
//
// }}}

/**
 * @file Enums.cpp
 * @author Paul Ward
 * @brief Various enums.
 */
 
#include "Enums.hpp"
#include "Utils.hpp"

#include <string>
#include <vector>
#include <ostream>

#include <boost/algorithm/string/join.hpp>

using namespace std;

ostream &
operator<<(ostream &os, const IncrementType &obj)
{
  switch (obj) {
    case IncrementType::ByMonths: os << "months";  break;
    case IncrementType::ByYears:  os << "years";   break;
    case IncrementType::ByDate:   os << "date";    break;
    case IncrementType::Simple:   os << "simple";  break;
    default:                      os << "<unset>"; break;
  }

  return os;
}

ostream &
operator<<(ostream &os, const IncrementMode &obj)
{
  vector<string> modes;

  if ((obj & IncrementMode::Major) != IncrementMode::None) {
    modes.push_back("major");
  }

  if ((obj & IncrementMode::Minor) != IncrementMode::None) {
    modes.push_back("minor");
  }

  if ((obj & IncrementMode::Build) != IncrementMode::None) {
    modes.push_back("build");
  }

  if ((obj & IncrementMode::Patch) != IncrementMode::None) {
    modes.push_back("patch");
  }

  if (modes.size() == 0) {
    os << "<not set>";
  } else {
    os << boost::algorithm::join(modes, ", ");
  }

  return os;
}

ostream &
operator<<(ostream &os, const OutputGroups &obj)
{
  vector<string> modes;

  if ((obj & OutputGroups::Basic) != OutputGroups::None) {
    modes.push_back("basic");
  }

  if ((obj & OutputGroups::Struct) != OutputGroups::None) {
    modes.push_back("struct");
  }

  if ((obj & OutputGroups::Doxygen) != OutputGroups::None) {
    modes.push_back("doxygen");
  }

  if (modes.size() == 0) {
    os << "<not set>";
  } else {
    os << boost::algorithm::join(modes, ", ");
  }

  return os;
}

// Enums.cpp ends here.
