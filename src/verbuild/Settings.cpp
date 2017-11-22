//
// Settings.cpp --- Program settings.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    30 May 2013 01:17:15
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
 * @file Settings.cpp
 * @author Paul Ward
 * @brief Program settings.
 */
 
#include "Settings.hpp"

#include <ostream>
#include <string>

using namespace std;

Settings::Settings()
{}

Settings::~Settings()
{}

void
Settings::set_increment_mode(IncrementMode obj)
{
  incr_mode_ = obj;
}

void
Settings::set_base_year(const int val)
{
  base_year_ = val;
}

const IncrementMode &
Settings::get_increment_mode() const
{
  return incr_mode_;
}

const int
Settings::get_base_year() const
{
  return base_year_;
}

ostream &
operator<<(ostream &os, const Settings &obj)
{
  os << "Increment mode: " << obj.get_increment_mode() << std::endl
     << "Base year:      " << obj.get_base_year();

  return os;
}

// Settings.cpp ends here.
