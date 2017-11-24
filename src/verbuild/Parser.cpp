//
// Parser.cpp --- Parser abstract implementation.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    23 Nov 2017 18:43:33
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
 * @file Parser.cpp
 * @author Paul Ward
 * @brief Parser abstract implementation.
 */
 
#include "Parser.hpp"

#include <exception>

using namespace std;

static int failval = 0;

Parser::Parser()
  : allowed_(),
    str_("")
{}

Parser::Parser(const std::string &)
  : allowed_(),
    str_("")
{}

Parser::~Parser()
{}

const int &
Parser::get() const
{
  throw runtime_error("not implemented");

  return failval;
}

void
Parser::set(const string &)
{
  throw runtime_error("not implemented");
}

const string &
Parser::to_string() const
{
  return str_;
}

const StringVector &
Parser::allowed_values()
{
  generate_allowed();
  return allowed_;
}

void
Parser::generate_allowed()
{
  throw runtime_error("not implemented");
}

void
Parser::parse(const std::string &)
{
  throw runtime_error("not implemented");
}

void
Parser::cache_string()
{
  throw runtime_error("not implemented");
}

ostream &
operator<<(ostream &os, const Parser &obj)
{
  os << obj.to_string();

  return os;
}

// Parser.cpp ends here.
