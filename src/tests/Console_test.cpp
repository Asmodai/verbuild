//
// Console_test.cpp --- Console tests.
//
// Copyright (c) 2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    22 Nov 2017 01:15:36
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
 * @file Console_test.cpp
 * @author Paul Ward
 * @brief Console tests.
 */
 
#define BOOST_TEST_MODULE Console_test
#include <boost/test/unit_test.hpp>

#include <string>
#include <iostream>
#include <sstream>
#include <ostream>

// Keep these in sync with Console.cpp!
#define ANSI_LIGHT_RED     "\033[1;31m"
#define ANSI_LIGHT_GREEN   "\033[1;32m"
#define ANSI_YELLOW        "\033[1;33m"
#define ANSI_LIGHT_BLUE    "\033[1;34m"
#define ANSI_LIGHT_MAGENTA "\033[1;35m"
#define ANSI_LIGHT_CYAN    "\033[1;36m"
#define ANSI_WHITE         "\033[1;37m"
#define ANSI_NONE          "\033[0m"

#include "../verbuild/Console.hpp"

struct fixtures {
  fixtures() {
    set_verbose(true);
    set_debug_level(DEBUG_EVERYTHING);
  }

  ~fixtures() {
  }
};

BOOST_GLOBAL_FIXTURE(fixtures);

BOOST_AUTO_TEST_SUITE(Console_test_suite)

BOOST_AUTO_TEST_CASE(ctor_test)
{
  Console obj;

  BOOST_CHECK_EQUAL(obj.get_stream(), &std::cerr);
}

BOOST_AUTO_TEST_CASE(accessor_test)
{
  Console obj(&std::cout);

  BOOST_CHECK_EQUAL(obj.get_stream(), &std::cout);
}

BOOST_AUTO_TEST_CASE(writer_default_fn)
{
  std::string       out("Test");
  std::stringstream ss;

  write_debug_output(&ss, out);

  BOOST_CHECK_EQUAL(ss.str(), out);
}

BOOST_AUTO_TEST_CASE(writer_recursive_fn)
{
  std::string       one("This");
  std::string       two("Is");
  int               three(3);
  std::string       four("Test");
  std::string       want("This Is 3 Test\n");
  std::stringstream ss;
  Console           obj(&ss);

  obj.write(one, two, three, four);

  BOOST_CHECK_EQUAL(ss.str(), want);
}

BOOST_AUTO_TEST_CASE(log_method_with_verbose)
{
  std::string        out("Test");
  std::ostringstream ss;
  std::stringstream  want;
  Console            obj(&ss);

  want << ANSI_WHITE << "["
       << ANSI_LIGHT_GREEN << "LOG"
       << ANSI_WHITE << "]"
       << ANSI_NONE << " "
       << out << "\n";

  set_verbose(true);
  obj.log().write(out);
  BOOST_CHECK_EQUAL(ss.str(), want.str());
}

BOOST_AUTO_TEST_CASE(log_method_without_verbose)
{
  std::string        out("Test");
  std::ostringstream ss;
  Console            obj(&ss);

  set_verbose(false);
  obj.log().write(out);
  BOOST_CHECK_EQUAL(ss.str(), "");
}

BOOST_AUTO_TEST_CASE(debug_method_with_everything)
{
  std::string        out("Test");
  std::ostringstream ss;
  std::stringstream  want;
  Console            obj(&ss);

  want << ANSI_WHITE << "["
       << ANSI_YELLOW << "DEBUG"
       << ANSI_WHITE << "]"
       << ANSI_NONE << " "
       << ANSI_WHITE << "[" << ANSI_LIGHT_CYAN
       << "test.cpp" << ":" << 666
       << ANSI_WHITE << "]: ["
       << ANSI_LIGHT_BLUE << "void derp" << ANSI_WHITE << "]"
       << ANSI_NONE << " "
       << out << "\n";

  set_debug_level(DEBUG_EVERYTHING);
  obj.debug(DEBUG_VERYHIGH, "test.cpp", 666, "void derp").write(out);
  BOOST_CHECK_EQUAL(ss.str(), want.str());
}

BOOST_AUTO_TEST_CASE(debug_method_with_none)
{
  std::string        out("Test");
  std::ostringstream ss;
  Console            obj(&ss);

  set_debug_level(DEBUG_NONE);
  obj.debug(DEBUG_VERYHIGH, "test.cpp", 666, "void derp").write(out);
  BOOST_CHECK_EQUAL(ss.str(), "");
}

BOOST_AUTO_TEST_CASE(debug_method_with_low_level)
{
  std::string        out("Test");
  std::ostringstream ss;
  Console            obj(&ss);

  set_debug_level(DEBUG_LOW);
  obj.debug(DEBUG_VERYHIGH, "test.cpp", 666, "void derp").write(out);
  BOOST_CHECK_EQUAL(ss.str(), "");
}

BOOST_AUTO_TEST_CASE(warn_method)
{
  std::string        out("Test");
  std::ostringstream ss;
  std::stringstream  want;
  Console            obj(&ss);

  want << ANSI_WHITE << "["
       << ANSI_LIGHT_MAGENTA << "WARN"
       << ANSI_WHITE << "]"
       << ANSI_NONE << " "
       << ANSI_WHITE << "[" << ANSI_LIGHT_CYAN
       << "test.cpp" << ":" << 666
       << ANSI_WHITE << "]: ["
       << ANSI_LIGHT_BLUE << "void derp" << ANSI_WHITE << "]"
       << ANSI_NONE << " "
       << out << "\n";

  obj.warn("test.cpp", 666, "void derp").write(out);
  BOOST_CHECK_EQUAL(ss.str(), want.str());
}

BOOST_AUTO_TEST_CASE(error_method)
{
  std::string        out("Test");
  std::ostringstream ss;
  std::stringstream  want;
  Console            obj(&ss);

  want << ANSI_WHITE << "["
       << ANSI_LIGHT_RED << "ERROR"
       << ANSI_WHITE << "]"
       << ANSI_NONE << " "
       << ANSI_WHITE << "[" << ANSI_LIGHT_CYAN
       << "test.cpp" << ":" << 666
       << ANSI_WHITE << "]: ["
       << ANSI_LIGHT_BLUE << "void derp" << ANSI_WHITE << "]"
       << ANSI_NONE << " "
       << out << "\n";

  obj.error("test.cpp", 666, "void derp").write(out);
  BOOST_CHECK_EQUAL(ss.str(), want.str());
}

BOOST_AUTO_TEST_CASE(fatal_method)
{
  std::string        out("Test");
  std::ostringstream ss;
  std::stringstream  want;
  Console            obj(&ss);

  want << ANSI_WHITE << "["
       << ANSI_LIGHT_RED << "FATAL"
       << ANSI_WHITE << "]"
       << ANSI_NONE << " "
       << out << "\n";

  obj.fatal().write(out);
  BOOST_CHECK_EQUAL(ss.str(), want.str());
}

BOOST_AUTO_TEST_CASE(ok_method)
{
  std::string        out("Test");
  std::ostringstream ss;
  std::stringstream  want;
  Console            obj(&ss);

  want << ANSI_WHITE << "["
       << ANSI_LIGHT_GREEN << "OK"
       << ANSI_WHITE << "]"
       << ANSI_NONE << " "
       << out << "\n";

  obj.ok().write(out);
  BOOST_CHECK_EQUAL(ss.str(), want.str());
}

BOOST_AUTO_TEST_SUITE_END()

// Console_test.cpp ends here.
