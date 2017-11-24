//
// GroupsParser.cpp --- Groups parser.
//
// Copyright (c) 2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    24 Nov 2017 02:55:38
//
// {{{ License:
//
// This program is free                                    software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software                       Foundation; either version 3
// of the                                                  License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY                                         WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this                                         program; if not, see <http://www.gnu.org/licenses/>.
//
// }}}
// {{{ Commentary:
//
// }}}

/**
 * @file GroupsParser.cpp
 * @author Paul Ward
 * @brief Groups parser.
 */
 
#include "Support.hpp"
#include "GroupsParser.hpp"
#include "Utils.hpp"
#include "Console.hpp"

#include <vector>
#include <sstream>
#include <ostream>

#include <boost/program_options.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/join.hpp>

using namespace std;
namespace       po = boost::program_options;

GroupsParser::GroupsParser()
  : groups_(OutputGroups::Basic)
{
  cache_string();
}

GroupsParser::GroupsParser(const string &other)
{
  parse(other);
  cache_string();
}

GroupsParser::~GroupsParser()
{}

const OutputGroups &
GroupsParser::get_groups() const
{
  return groups_;
}

void
GroupsParser::set_groups(const OutputGroups val)
{
  groups_ = val;
  cache_string();
}

void
GroupsParser::set_groups(const string &val)
{
  parse(val);
  cache_string();
}

void
GroupsParser::generate_allowed()
{
  DSAY(DEBUG_VERYHIGH, "allowed has size of", allowed_.size());

  if (allowed_.size() > 0) {
    return;
  }

  DSAY(DEBUG_VERYHIGH, "Initialising allowed values.");

  allowed_.push_back("basic");
  allowed_.push_back("struct");
  allowed_.push_back("doxygen");
  allowed_.push_back("all");
}

void
GroupsParser::parse(const string &what)
{
  StringVector list;
  string       lc(what);

  downcase(lc);
  delete_whitespace(lc);
  groups_ = OutputGroups::None;

  boost::algorithm::split(list, what, boost::is_any_of(","));

  for (auto &it : list) {
    if (it == "basic") {
      groups_ |= OutputGroups::Basic;
      continue;
    }

    if (it == "struct") {
      groups_ |= OutputGroups::Struct;
      continue;
    }

    if (it == "doxygen") {
      groups_ |= OutputGroups::Doxygen;
      continue;
    }

    if (it == "all") {
      groups_ |= OutputGroups::All;
      return;
    }
  }
}

void
GroupsParser::cache_string()
{
  stringstream ss;
  StringVector list;

  if ((groups_ & OutputGroups::All) == OutputGroups::All) {
    list.push_back("all");
    goto done;
  }

  if ((groups_ & OutputGroups::Basic) != OutputGroups::None) {
    list.push_back("basic");
  }

  if ((groups_ & OutputGroups::Struct) != OutputGroups::None) {
    list.push_back("struct");
  }

  if ((groups_ & OutputGroups::Doxygen) != OutputGroups::None) {
    list.push_back("doxygen");
  }

done:
  ss << boost::algorithm::join(list, ",");
  str_.assign(ss.str());
  ss.clear();
}

void
validate(boost::any         &v,
         const StringVector &vals,
         GroupsParser       *,
         int)
{
  po::validators::check_first_occurrence(v);

  const string &s       = po::validators::get_single_string(vals);
  GroupsParser  parser;
  StringVector  allowed = parser.allowed_values();
  string        lc(s);
  StringVector  list;

  downcase(lc);
  delete_whitespace(lc);

  boost::algorithm::split(list, s, boost::is_any_of(","));

  DSAY(DEBUG_HIGH, "Attempting to match output group.");
  for (auto &it : list) {
    if (find(allowed.begin(), allowed.end(), it) == allowed.end()) {
      DSAY(DEBUG_HIGH, "Could not find output group", it);
      stringstream ss;

      ss << "Invalid output group: " << s;
      throw std::invalid_argument(ss.str().c_str());
    }
  }

  DSAY(DEBUG_HIGH, "Output groups found.");
  v = boost::any(GroupsParser{ lc });
}

// GroupsParser.cpp ends here.
