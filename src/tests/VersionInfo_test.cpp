//
// VersionInfo_test.cpp --- VersionInfo tests.
//
// Copyright (c) 2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    22 Nov 2017 18:04:35
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
 * @file VersionInfo_test.cpp
 * @author Paul Ward
 * @brief VersionInfo tests.
 */
 
#define BOOST_TEST_MODULE VersionInfo_test
#include <boost/test/unit_test.hpp>

#include <string>
#include <iostream>
#include <sstream>
#include <ostream>

#include "../verbuild/VersionInfo.hpp"
#include "../verbuild/Console.hpp"

namespace date = boost::gregorian;
using namespace std;


struct fixtures {
  fixtures() {
    set_debug_level(0);
  }

  ~fixtures() {
  }
};

BOOST_GLOBAL_FIXTURE(fixtures);

BOOST_AUTO_TEST_SUITE(VersionInfo_test_suite)

BOOST_AUTO_TEST_CASE(ctor_tests)
{
  VersionInfo obj1;
  VersionInfo obj2(1, 2, 3, 4, 2017, IncrementType::ByYears);

  BOOST_CHECK_EQUAL(obj1.get_major(), 0);
  BOOST_CHECK_EQUAL(obj1.get_minor(), 0);
  BOOST_CHECK_EQUAL(obj1.get_build(), 0);
  BOOST_CHECK_EQUAL(obj1.get_patch(), 0);
  BOOST_CHECK_EQUAL(obj1.get_base_year(), 1970);
  BOOST_CHECK_EQUAL(obj1.get_increment_type(), IncrementType::Simple);
  BOOST_CHECK_EQUAL(obj1.get_overflow(), false);

  BOOST_CHECK_EQUAL(obj2.get_major(), 1);
  BOOST_CHECK_EQUAL(obj2.get_minor(), 2);
  BOOST_CHECK_EQUAL(obj2.get_build(), 3);
  BOOST_CHECK_EQUAL(obj2.get_patch(), 4);
  BOOST_CHECK_EQUAL(obj2.get_base_year(), 2017);
  BOOST_CHECK_EQUAL(obj2.get_increment_type(), IncrementType::ByYears);
  BOOST_CHECK_EQUAL(obj2.get_overflow(), false);
}

BOOST_AUTO_TEST_CASE(accessor_tests)
{
  VersionInfo obj;

  obj.set_major(1);
  obj.set_minor(2);
  obj.set_build(3);
  obj.set_patch(4);
  obj.set_base_year(2017);
  obj.set_increment_type(IncrementType::ByDate);
  obj.set_overflow(true);

  BOOST_CHECK_EQUAL(obj.get_major(), 1);
  BOOST_CHECK_EQUAL(obj.get_minor(), 2);
  BOOST_CHECK_EQUAL(obj.get_build(), 3);
  BOOST_CHECK_EQUAL(obj.get_patch(), 4);
  BOOST_CHECK_EQUAL(obj.get_base_year(), 2017);
  BOOST_CHECK_EQUAL(obj.get_increment_type(), IncrementType::ByDate);
  BOOST_CHECK_EQUAL(obj.get_overflow(), true);
}

BOOST_AUTO_TEST_CASE(string_conversion)
{
  VersionInfo obj(1, 2, 3, 4, 2017, IncrementType::Simple);
  string      want("1.2.3.4");

  BOOST_CHECK_EQUAL(obj.to_string(), want);
}

BOOST_AUTO_TEST_CASE(date_conversion)
{
  VersionInfo  obj(1, 0, 41122, 0, 2013, IncrementType::ByYears);
  string       want("2017-Nov-22");
  stringstream ss;
  
  ss << obj.to_date();
  
  BOOST_CHECK_EQUAL(ss.str(), want);
}

BOOST_AUTO_TEST_CASE(incrementing)
{
  VersionInfo   o1(1, 2, 20171121, 0, 2017, IncrementType::ByDate);
  VersionInfo   o2(1, 2, 1121, 0, 2017, IncrementType::ByMonths);
  VersionInfo   o3(1, 2, 41121, 0, 2013, IncrementType::ByYears);
  VersionInfo   o4(1, 2, 1, 0, 2013, IncrementType::Simple);
  string        w1("1.2.20171122.0");
  string        w2("1.2.1122.0");
  string        w3("1.2.41122.0");
  string        w4("1.2.2.0");
  IncrementMode mode(IncrementMode::Build);
  
  o1.increment(mode);
  o2.increment(mode);
  o3.increment(mode);
  o4.increment(mode);
  
  BOOST_CHECK_EQUAL(o1.to_string(), w1);
  BOOST_CHECK_EQUAL(o2.to_string(), w2);
  BOOST_CHECK_EQUAL(o3.to_string(), w3);
  BOOST_CHECK_EQUAL(o4.to_string(), w4);
}

BOOST_AUTO_TEST_CASE(operators)
{
  VersionInfo o1(1, 2, 1, 0, 2013, IncrementType::Simple);
  VersionInfo o2(1, 2, 3, 0, 2017, IncrementType::Simple);
  VersionInfo o3(1, 2, 1, 0, 2013, IncrementType::Simple);
  bool        r1(o1 == o2);
  bool        r2(o1 != o2);
  bool        r3(o1 == o3);

  BOOST_CHECK_EQUAL(r1, false);
  BOOST_CHECK_EQUAL(r2, true);
  BOOST_CHECK_EQUAL(r3, true);
}

BOOST_AUTO_TEST_CASE(ostream_operator)
{
  VersionInfo  o1(1, 2, 3, 4, 2013, IncrementType::Simple);
  stringstream ss;
  string       want("1.2.3.4");
  
  ss << o1;

  BOOST_CHECK_EQUAL(ss.str(), want);
}

BOOST_AUTO_TEST_SUITE_END()

// VersionInfo_test.cpp ends here.
