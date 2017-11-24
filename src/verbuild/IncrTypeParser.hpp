//
// IncrTypeParser.hpp --- Increment type parser.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    23 Nov 2017 18:05:02
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
 * @file IncrTypeParser.hpp
 * @author Paul Ward
 * @brief Increment type parser.
 */

#pragma once
#ifndef _IncrTypeParser_hpp_
#define _IncrTypeParser_hpp_

#include "Enums.hpp"
#include "Parser.hpp"

#include <string>
#include <ostream>
#include <vector>

#include <boost/any.hpp>

class IncrTypeParser
  : public Parser
{
private:
  IncrementType type_;

public:
  IncrTypeParser();
  IncrTypeParser(const std::string &);
  ~IncrTypeParser();

  const IncrementType &get_type() const;

  void set_type(const IncrementType);
  void set_type(const std::string &);

private:
  void generate_allowed();
  void parse(const std::string &);
  void cache_string();
};

void validate(boost::any         &,
              const StringVector &,
              IncrTypeParser     *,
              int);

#endif // !_IncrTypeParser_hpp_

// IncrTypeParser.hpp ends here.
