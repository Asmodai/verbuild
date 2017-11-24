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
#include <regex>
#include <cstdlib>

#include <boost/program_options.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/join.hpp>

using namespace std;
namespace po = boost::program_options;

IncrModeParser::LiteralValue
extract_literal(string &val)
{
  IncrModeParser::LiteralValue res(false, 0);

  try {
    res.first = true;
    res.second = static_cast<uint32_t>(stoi(val));
  }
  catch (invalid_argument &e) {
    DSAY(DEBUG_HIGH, "Invalid argument: ", e.what());
    res.first = false;
    res.second = 0;
  }
  catch (out_of_range &) {
    DSAY(DEBUG_HIGH,
         "The given number is too large. "
         "Defaulting to 'ignore'.");
    res.first = false;
    res.second = 0;
  }
  catch (...) {
    DSAY(DEBUG_EVERYTHING, "Unhandled exception.");
    FATAL("Terminating.");
    exit(EXIT_FAILURE);
  }

  return res;
}

string
make_string_element(IncrementMode                &mode,
                    IncrModeParser::LiteralArray &vals,
                    IncrementMode                 what,
                    size_t                        offset)
{
  if (vals.at(offset).first) {
    return to_string(vals.at(offset).second);
  }

  if ((mode & what) != IncrementMode::None) {
    return "+";
  }

  return "*";
}

void
set_field(const char                   *field,
          StringVector                 &list,
          IncrementMode                &mode,
          IncrementMode                 set,
          IncrModeParser::LiteralArray &literals,
          size_t                        offset)
{
  switch (list.at(offset).at(0)) {
    case '+':
      mode |= set;
      DSAY(DEBUG_MEDIUM, field, "set to 'increment'");
      break;
    case '*':
      mode |= IncrementMode::None;
      DSAY(DEBUG_MEDIUM, field, "set to 'ignore'");
      break;
    default:
      mode |= IncrementMode::None;
      literals.at(offset) = extract_literal(list.at(offset));
      DSAY(DEBUG_MEDIUM,
        field,
        "set to literal:",
        literals.at(offset).second);
      break;
  }
}

IncrModeParser::IncrModeParser()
  : literals_(),
    mode_(IncrementMode::None)
{
  cache_string();
}

IncrModeParser::IncrModeParser(const string &other)
  : literals_(),
    mode_(IncrementMode::None)
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

bool
IncrModeParser::get_literal(size_t index, std::uint32_t &out) const
{
  if (index < 0 || index > 4) {
    return false;
  }

  if (literals_.at(index).first) {
    out = literals_.at(index).second;
    return true;
  }

  return false;
}

void
IncrModeParser::generate_allowed()
{
  if (allowed_.size() > 0) {
    return;
  }

  allowed_.push_back("major");
  allowed_.push_back("minor");
  allowed_.push_back("build");
  allowed_.push_back("patch");
}

void
IncrModeParser::parse(const string &what)
{
  StringVector list;

  mode_ = IncrementMode::None;
  boost::algorithm::split(list, what, boost::is_any_of("."));

  if (list.size() != 4) {
    throw std::runtime_error("Could not parse!");
  }

  set_field("Major", list, mode_, IncrementMode::Major, literals_, 0);
  set_field("Minor", list, mode_, IncrementMode::Minor, literals_, 1);
  set_field("Build", list, mode_, IncrementMode::Build, literals_, 2);
  set_field("Patch", list, mode_, IncrementMode::Patch, literals_, 3);
}

void
IncrModeParser::cache_string()
{
  stringstream ss;
  StringVector modes;

  modes.push_back(make_string_element(mode_, literals_, IncrementMode::Major, 0));
  modes.push_back(make_string_element(mode_, literals_, IncrementMode::Minor, 1));
  modes.push_back(make_string_element(mode_, literals_, IncrementMode::Build, 2));
  modes.push_back(make_string_element(mode_, literals_, IncrementMode::Patch, 3));

  ss << boost::algorithm::join(modes, ".");
  str_.assign(ss.str());
  ss.clear();
}

void
validate(boost::any         &v,
         const StringVector &vals,
         IncrModeParser     *,
         int)
{
  po::validators::check_first_occurrence(v);

  const string &s = po::validators::get_single_string(vals);

  regex  re("([\\*\\+]|\\d+)\\.([\\*\\+]|\\d+)\\.([\\*\\+]|\\d+)\\.([\\*\\+]|\\d+)");
  smatch matches;
  bool   matched(false);

  DSAY(DEBUG_HIGH, "Attempting to match format with regex.");
  matched = regex_match(s, matches, re);

  if (!matched || matches.size() != 5) {
    DSAY(DEBUG_HIGH, "Format", s, "did not match regex.");
    stringstream ss;

    ss << "Invalid format: " << s;
    throw std::invalid_argument(ss.str().c_str());
  }

  DSAY(DEBUG_HIGH, "Regex matched.");
  v = boost::any(IncrModeParser{ s });
}

// IncrModeParser.cpp ends here.
