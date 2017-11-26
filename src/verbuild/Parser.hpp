//
// Parser.hpp --- Parser abstract.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    23 Nov 2017 18:36:46
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
 * @brief Parser abstract.
 */

#pragma once
#ifndef _Parser_hpp_
#define _Parser_hpp_

#include "Utils.hpp"

#include <string>
#include <ostream>

class Parser
{
protected:
  StringVector allowed_;
  std::string str_;

public:
  Parser();
  Parser(const std::string &);
  virtual ~Parser();

  virtual const int &get() const;
  virtual void set(const std::string &);

  const std::string &to_string() const;

  const StringVector &allowed_values();

private:
  virtual void generate_allowed();
  virtual void parse(const std::string &);
  virtual void cache_string();

public:
  friend std::ostream &operator<<(std::ostream &, const Parser &);
};
  
#endif // !_Parser_hpp_

// Parser.hpp ends here.
