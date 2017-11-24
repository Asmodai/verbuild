//
// GroupsParser.hpp --- Group parser.
//
// Copyright (c) 2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    24 Nov 2017 02:53:47
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
 * @file GroupsParser.hpp
 * @author Paul Ward
 * @brief Group parser.
 */

#pragma once
#ifndef _GroupsParser_hpp_
#define _GroupsParser_hpp_

#include "Support.hpp"
#include "Enums.hpp"
#include "Parser.hpp"
#include "Utils.hpp"

#include <string>
#include <ostream>
#include <vector>
#include <array>
#include <utility>

#include <boost/any.hpp>

class GroupsParser
  : public Parser
{
private:
  OutputGroups groups_;

public:
  GroupsParser();
  GroupsParser(const std::string &);
  ~GroupsParser();

  const OutputGroups &get_groups() const;

  void set_groups(const OutputGroups);
  void set_groups(const std::string &);

private:
  void generate_allowed();
  void parse(const std::string &);
  void cache_string();
};

void validate(boost::any         &,
              const StringVector &,
              GroupsParser       *,
              int);

#endif // !_GroupsParser_hpp_

// GroupsParser.hpp ends here.
