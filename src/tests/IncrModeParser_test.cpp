//
// IncrModeParser_test.cpp --- Increment mode parser test.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    21 Nov 2017 23:45:46
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
 * @file IncrModeParser_test.cpp
 * @author Paul Ward
 * @brief Increment mode parser test.
 */
 
#define BOOST_TEST_MODULE IncrModeParser_test
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <string>
#include <sstream>

#include <boost/lexical_cast.hpp>

#include "../verbuild/Console.hpp"
#include "../verbuild/Enums.hpp"
#include "../verbuild/IncrModeParser.hpp"

BOOST_AUTO_TEST_SUITE(IncrModeParser_test_suite)

BOOST_AUTO_TEST_CASE(default_ctor_test)
{
  IncrModeParser obj0;

  BOOST_CHECK_EQUAL(obj0.get_mode(), IncrementMode::None);
}

BOOST_AUTO_TEST_CASE(good_ctor_value_test)
{
  const std::string good("*.*.*.+");
  IncrModeParser    obj1(good);

  BOOST_CHECK_EQUAL(obj1.get_mode(), IncrementMode::Patch);
}

BOOST_AUTO_TEST_CASE(bad_ctor_value_test)
{
  const std::string bad("junk");

  BOOST_REQUIRE_THROW(
    IncrModeParser obj2(bad),
    std::runtime_error
  );
}

BOOST_AUTO_TEST_CASE(accessor_test)
{
  const IncrementMode mode(IncrementMode::MinorAndBuild);
  IncrModeParser      obj;

  obj.set_mode(mode);

  BOOST_CHECK_EQUAL(obj.get_mode(), mode);
}

BOOST_AUTO_TEST_CASE(ostream_test)
{
  const std::string   expected("minor, build, patch");
  IncrModeParser      obj("*.+.+.+");
  std::stringstream   ss;

  ss << obj.get_mode();

  BOOST_CHECK_EQUAL(ss.str(), expected);
}

BOOST_AUTO_TEST_CASE(po_validate_test)
{
  const std::string        expected("minor, build, patch");
  std::vector<std::string> args;
  std::string              input("*.+.+.+");
  IncrModeParser           obj;
  boost::any               v;
  std::stringstream        ss;

  args.push_back(input);
  validate(v, args, &obj, 0);
  obj = boost::any_cast<IncrModeParser>(v);
  ss << obj.get_mode();

  BOOST_CHECK_EQUAL(ss.str(), expected);
}

BOOST_AUTO_TEST_SUITE_END()

// IncrModeParser_test.cpp ends here.
