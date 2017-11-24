//
// TransformParser.cpp --- Transform parser implementation.
//
// Copyright (c) 2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    24 Nov 2017 00:42:44
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
 * @file TransformParser.cpp
 * @author Paul Ward
 * @brief Transform parser implementation.
 */
 
#include "Support.hpp"
#include "TransformParser.hpp"
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

TransformParser::TransformParser()
{
  str_ = "";
}

TransformParser::TransformParser(const string &other)
{
  str_.assign(other);
}

TransformParser::~TransformParser()
{}

void
TransformParser::generate_allowed()
{
  if (allowed_.size() > 0) {
    return;
  }

  for (auto it = TRANSFORM_BEGIN(); it != TRANSFORM_END(); it++) {
    allowed_.push_back(it->first);
  }
}

void
TransformParser::parse(const std::string &)
{
  /* Does nothing. */
}

void
TransformParser::cache_string()
{
  /* Does nothing. */
}

void
validate(boost::any         &v,
         const StringVector &vals,
         TransformParser    *,
         int)
{
  po::validators::check_first_occurrence(v);

  const string &s = po::validators::get_single_string(vals);
  string        lc(s);

  downcase(lc);

  auto it = FIND_TRANSFORM_BUILDER(lc);

  DSAY(DEBUG_HIGH, "Attempting to match transform.");
  if (it == TRANSFORM_BUILDER_END()) {
    stringstream ss;

    DSAY(DEBUG_HIGH, "Transform not found.");
    ss << "Invalid transform: "<< s;
    throw invalid_argument(ss.str().c_str());
  }

  DSAY(DEBUG_HIGH, "Using transform", lc);
  v = boost::any(TransformParser{ lc });
}

// TransformParser.cpp ends here.
