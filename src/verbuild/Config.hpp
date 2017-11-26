//
// Config.hpp --- Configuration.
//
// Copyright (c) 2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    24 Nov 2017 22:00:15
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
 * @file Config.hpp
 * @author Paul Ward
 * @brief Configuration.
 */

#pragma once
#ifndef _Config_hpp_
#define _Config_hpp_

#include "Support.hpp"
#include "Enums.hpp"

#include <string>

struct Config
{
  std::uint32_t base_year;
  IncrementMode incr_mode;
  IncrementType incr_type;
  OutputGroups  groups;
  std::string   transform;
  std::string   prefix;
  bool          create;
  std::string   filename;

  Config() {};
  Config(const Config &) = delete;
  ~Config() {};

  void print();
};


#endif // !_Config_hpp_

// Config.hpp ends here.
