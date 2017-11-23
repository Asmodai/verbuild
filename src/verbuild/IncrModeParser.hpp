//
// IncrModeParser.hpp --- Increment mode parser
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    22 Nov 2017 00:06:49
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
 * @file IncrModeParser.hpp
 * @author Paul Ward
 * @brief Increment mode parser
 */

#pragma once
#ifndef _IncrModeParser_hpp_
#define _IncrModeParser_hpp_

#include "Enums.hpp"

#include <string>
#include <ostream>
#include <vector>

#include <boost/any.hpp>

class IncrModeParser
{
private:
  IncrementMode mode_;
  std::string   str_;

public:
  IncrModeParser();
  IncrModeParser(const std::string &);
  ~IncrModeParser();

  const IncrementMode &get_mode() const;
  void set_mode(const IncrementMode);
  void set_mode(const std::string &);

  const std::string &to_string() const;

private:
  void parse(const std::string &);
  void cache_string();

public:
  friend std::ostream &operator<<(std::ostream &, const IncrModeParser &);
};

void validate(boost::any &,
              const std::vector<std::string> &,
              IncrModeParser *,
              int);


#endif // !_IncrModeParser_hpp_

// IncrModeParser.hpp ends here.
