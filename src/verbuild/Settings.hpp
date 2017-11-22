//
// Settings.hpp --- Program settings.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    30 May 2013 01:16:19
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
 * @file Settings.hpp
 * @author Paul Ward
 * @brief Program settings.
 */

#pragma once
#ifndef _Settings_hpp_
#define _Settings_hpp_

#include "Support.hpp"
#include "Enums.hpp"

#include <ostream>
#include <string>

class Settings
{
private:
  std::string   outfile_;
  int           base_year_;
  IncrementMode incr_mode_;
  IncrementType incr_type_;


public:
  Settings();
  ~Settings();

  void set_increment_mode(IncrementMode);
  void set_base_year(const int);

  const IncrementMode &get_increment_mode() const;
  const int            get_base_year() const;

public:
  friend std::ostream &operator<<(std::ostream &, const Settings &);
};

#endif // !_Settings_hpp_

// Settings.hpp ends here.
