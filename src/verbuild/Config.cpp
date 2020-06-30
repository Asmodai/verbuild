//
// Config.cpp --- Configuration.
//
// Copyright (c) 2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    25 Nov 2017 22:06:07
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
 * @file Config.cpp
 * @author Paul Ward
 * @brief Configuration.
 */

#include "Config.hpp"
#include "Console.hpp"
#include "Utils.hpp"

#include <iostream>
#include <sstream>

using namespace std;

void
Config::print() const
{
  ListPairVector lpv;

  lpv.push_back(ListPair("File name", filename));
  lpv.push_back(ListPair("Create file", (create ? "Yes" : "No")));
  lpv.push_back(ListPair("Transform", transform));
  lpv.push_back(ListPair("Prefix", prefix));
  lpv.push_back(ListPair("Base  year", to_string(base_year)));

  {
    stringstream ss;

    ss << incr_mode;
    lpv.push_back(ListPair("Increment format", ss.str()));
  }

  {
    stringstream ss;

    ss << incr_type;
    lpv.push_back(ListPair("Increment type", ss.str()));
  }

  {
    stringstream ss;

    ss << groups;
    lpv.push_back(ListPair("Groups", ss.str()));
  }
  
  Console(&cout).write_pairs(lpv, 4);
}

// Config.cpp ends here.
