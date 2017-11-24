//
// TransformParser.hpp --- Transform parser.
//
// Copyright (c) 2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    24 Nov 2017 00:37:50
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
 * @file TransformParser.hpp
 * @author Paul Ward
 * @brief Transform parser.
 */

#pragma once
#ifndef _TransformParser_hpp_
#define _TransformParser_hpp_

#include "Support.hpp"
#include "Enums.hpp"
#include "Parser.hpp"
#include "Utils.hpp"
#include "Transform.hpp"

#include <string>
#include <ostream>
#include <vector>
#include <array>
#include <utility>

#include <boost/any.hpp>

class TransformParser
  : public Parser
{
public:
  TransformParser();
  TransformParser(const std::string &);
  ~TransformParser();

private:
  void generate_allowed();
  void parse(const std::string &);
  void cache_string();
};

void validate(boost::any         &,
              const StringVector &,
              TransformParser    *,
              int);

#endif // !_TransformParser_hpp_

// TransformParser.hpp ends here.
