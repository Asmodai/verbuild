//
// IncrTypeParser.cpp --- Increment type parser implementation.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    23 Nov 2017 18:07:56
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
 * @file IncrTypeParser.cpp
 * @author Paul Ward
 * @brief Increment type parser implementation.
 */
 
#include "Support.hpp"
#include "IncrTypeParser.hpp"
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

IncrTypeParser::IncrTypeParser()
  : type_(IncrementType::Simple)
{
  cache_string();
}

IncrTypeParser::IncrTypeParser(const string &other)
{
  parse(other);
  cache_string();
}

IncrTypeParser::~IncrTypeParser()
{}

const IncrementType &
IncrTypeParser::get_type() const
{
  return type_;
}

void
IncrTypeParser::set_type(const IncrementType val)
{
  type_ = val;
  cache_string();
}

void
IncrTypeParser::set_type(const string &val)
{
  parse(val);
  cache_string();
}

void
IncrTypeParser::generate_allowed()
{
  if (allowed_.size() > 0) {
    return;
  }

  allowed_.push_back("simple");
  allowed_.push_back("bymonths");
  allowed_.push_back("byyears");
  allowed_.push_back("bydate");
}

void
IncrTypeParser::parse(const string &what)
{
  string lc(what);

  downcase(lc);

  // Meh.
  if (lc == "simple") {
    type_ = IncrementType::Simple;
  } else if (lc == "bymonths") {
    type_ = IncrementType::ByMonths;
  } else if (lc == "byyears") {
    type_ = IncrementType::ByYears;
  } else if (lc == "bydate") {
    type_ = IncrementType::ByDate;
  }
}

void
IncrTypeParser::cache_string()
{
  stringstream ss;

  ss << type_;

  str_.assign(ss.str());
  ss.clear();
}

void
validate(boost::any         &v,
         const StringVector &vals,
         IncrTypeParser     *,
         int)
{
  static StringVector allowed;

  po::validators::check_first_occurrence(v);

  const string &s = po::validators::get_single_string(vals);
  string        lc(s);

  downcase(lc);

  if (allowed.size() == 0) {
    allowed.push_back("simple");
    allowed.push_back("byyears");
    allowed.push_back("bymonths");
    allowed.push_back("bydate");
  }

  if (find(allowed.begin(), allowed.end(), lc) == allowed.end()) {
    stringstream ss;
    
    ss << "Invalid type: " << s;
    throw invalid_argument(ss.str().c_str());
  }

  v = boost::any(IncrTypeParser{ s });
}

// IncrTypeParser.cpp ends here.
