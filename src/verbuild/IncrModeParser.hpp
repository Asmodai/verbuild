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

#include "Support.hpp"
#include "Enums.hpp"
#include "Parser.hpp"

#include <string>
#include <ostream>
#include <vector>
#include <array>
#include <utility>

#include <boost/any.hpp>

#define LITERAL_MAJOR    0
#define LITERAL_MINOR    1
#define LITERAL_BUILD    2
#define LITERAL_PATCH    3

class IncrModeParser
  : public Parser
{
public:
  typedef std::pair<bool, std::uint32_t> LiteralValue;
  typedef std::array<LiteralValue, 4>    LiteralArray;

private:
  LiteralArray  literals_;
  IncrementMode mode_ = IncrementMode::None;

public:
  IncrModeParser();
  IncrModeParser(const std::string &);
  ~IncrModeParser();

  const IncrementMode &get_mode() const;

  void set_mode(const IncrementMode);
  void set_mode(const std::string &);

  bool get_literal(size_t, std::uint32_t &) const;

private:
  void generate_allowed();
  void parse(const std::string &);
  void cache_string();
};

void validate(boost::any         &,
              const StringVector &,
              IncrModeParser     *,
              int);

#endif // !_IncrModeParser_hpp_

// IncrModeParser.hpp ends here.
