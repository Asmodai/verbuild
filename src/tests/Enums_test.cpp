//
// Enums_test.cpp --- Enums test.
//
// Copyright (c) 2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    22 Nov 2017 01:05:08
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
 * @file Enums_test.cpp
 * @author Paul Ward
 * @brief Enums test.
 */
 
#define BOOST_TEST_MODULE Enums_test
#include <boost/test/unit_test.hpp>

#include <sstream>

#include "../verbuild/Enums.hpp"

BOOST_AUTO_TEST_SUITE(Enums_test_suite)

BOOST_AUTO_TEST_CASE(IncrementType_ostream)
{
  IncrementType     test(IncrementType::Simple);
  std::stringstream ss;

  ss << test;

  BOOST_CHECK_EQUAL(ss.str(), "simple");
}

BOOST_AUTO_TEST_CASE(IncrementMode_ostream)
{
  IncrementMode     test(IncrementMode::Patch);
  std::stringstream ss;

  ss << test;

  BOOST_CHECK_EQUAL(ss.str(), "patch");
}

BOOST_AUTO_TEST_CASE(OutputMode_ostream)
{
  OutputMode        test(OutputMode::Doxygen);
  std::stringstream ss;

  ss << test;

  BOOST_CHECK_EQUAL(ss.str(), "doxygen");
}

BOOST_AUTO_TEST_SUITE_END()

// Enums_test.cpp ends here.
