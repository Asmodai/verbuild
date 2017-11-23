//
// IncrModeParser.cpp --- Increment mode parser.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    22 Nov 2017 00:05:06
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
 * @file IncrModeParser.cpp
 * @author Paul Ward
 * @brief Increment mode parser.
 */
 
#include "Support.hpp"
#include "IncrModeParser.hpp"
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
namespace po = boost::program_options;

IncrModeParser::IncrModeParser()
  : mode_(IncrementMode::None)
{
  cache_string();
}

IncrModeParser::IncrModeParser(const string &other)
{
  parse(other);
  cache_string();
}

IncrModeParser::~IncrModeParser()
{}

const IncrementMode &
IncrModeParser::get_mode() const
{
  return mode_;
}

void
IncrModeParser::set_mode(const IncrementMode val)
{
  mode_ = val;
  cache_string();
}

void
IncrModeParser::set_mode(const std::string &val)
{
  parse(val);
  cache_string();
}

const string &
IncrModeParser::to_string() const
{
  return str_;
}

void
IncrModeParser::parse(const string &what)
{
  vector<string> list;
  
  mode_ = IncrementMode::None;
  boost::algorithm::split(list, what, boost::is_any_of("."));

  if (list.size() != 4) {
    throw std::runtime_error("Could not parse!");
  }

  mode_ |= (list.at(0).at(0) == '+'
    ? IncrementMode::Major
    : IncrementMode::None);

  mode_ |= (list.at(1).at(0) == '+'
    ? IncrementMode::Minor
    : IncrementMode::None);

  mode_ |= (list.at(2).at(0) == '+'
    ? IncrementMode::Build
    : IncrementMode::None);

  mode_ |= (list.at(3).at(0) == '+'
    ? IncrementMode::Patch
    : IncrementMode::None);
}

void
IncrModeParser::cache_string()
{
  stringstream    ss;
  vector<string>  modes;

  if ((mode_ & IncrementMode::Major) != IncrementMode::None) {
    modes.push_back("+");
  } else {
    modes.push_back("*");
  }

  if ((mode_ & IncrementMode::Minor) != IncrementMode::None) {
    modes.push_back("+");
  } else {
    modes.push_back("*");
  }

  if ((mode_ & IncrementMode::Build) != IncrementMode::None) {
    modes.push_back("+");
  } else {
    modes.push_back("*");
  }

  if ((mode_ & IncrementMode::Patch) != IncrementMode::None) {
    modes.push_back("+");
  } else {
    modes.push_back("*");
  }

  ss << boost::algorithm::join(modes, ".");
  str_.assign(ss.str());
  ss.clear();
}

ostream &
operator<<(ostream &os, const IncrModeParser &obj)
{
  os << obj.to_string();

  return os;
}

void
validate(boost::any &v,
         const vector<string> &vals,
         IncrModeParser *,
         int)
{
  po::validators::check_first_occurrence(v);

  const string &s  = po::validators::get_single_string(vals);
  size_t        n  = count(s.begin(), s.end(), '.');
  bool          ok = all_of(s.begin(), s.end(), [](char i) {
      return (i == '*' || i == '+' || i == '.');
    });

  if (n != 3 || s.length() != 7 || !ok) {
    stringstream ss;

    ss << "Invalid format: " << s;
    throw std::invalid_argument(ss.str().c_str());
  }

  v = boost::any(IncrModeParser{ s });
}

// IncrModeParser.cpp ends here.
