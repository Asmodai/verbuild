//
// Console.hpp --- Console utilities.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    21 Nov 2017 23:59:01
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
 * @file Console.hpp
 * @author Paul Ward
 * @brief Console utilities.
 */

#pragma once
#ifndef _Console_hpp_
#define _Console_hpp_

#include "Support.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <ostream>
#include <utility>

#define DEBUG_EVERYTHING 9
#define DEBUG_VERYHIGH   4
#define DEBUG_HIGH       3
#define DEBUG_MEDIUM     2
#define DEBUG_LOW        1
#define DEBUG_NONE       0

typedef std::pair<std::string, std::string> ListPair;
typedef std::vector<ListPair>               ListPairVector;

template <typename TF>
void
write_debug_output(std::ostream *out, TF const &val)
{
  *out << val;
}

class Console
{
private:
  std::ostream *out_;

public:
  Console();
  Console(std::ostream *);

  std::ostream *get_stream() const;

  template <typename First, typename ...Rest>
  void write(First const &val, Rest const &...rest) {
    write_debug_output(out_, val);
    *out_ << " ";
    write(rest...);
  }

  template <typename First>
  void write(First const &val) {
    write_debug_output(out_, val);
    *out_ << std::endl;
  }

  void write() {
    *out_ << std::endl;
  }

  void write_pairs(ListPairVector &) const;

  Console &log();
  Console &debug(const int, const char *, const int, const char *);
  Console &warn(const char *, const int, const char *);
  Console &error(const char *, const int, const char *);

  Console &fatal();
  Console &ok();
};

extern void set_verbose(bool);
extern void set_debug_level(int);
extern bool debug_level_met(int);

#define LSAY(...)                                                       \
  Console(&std::cout)                                                   \
      .log()                                                            \
      .write(__VA_ARGS__)
#define DSAY(__l, ...)                                                  \
  Console()                                                             \
      .debug(__l, __FILE__, __LINE__, __PRETTY_FUNCTION__)              \
      .write(__VA_ARGS__)
#define WSAY(...)                                                       \
  Console()                                                             \
      .warn(__FILE__, __LINE__, __PRETTY_FUNCTION__)                    \
      .write(__VA_ARGS__)
#define ESAY(...)                                                       \
  Console()                                                             \
      .error(__FILE__, __LINE__, __PRETTY_FUNCTION__)                   \
      .write(__VA_ARGS__)

#define FATAL(...) Console(&std::cout).fatal().write(__VA_ARGS__)
#define OK(...)    Console(&std::cout).ok().write(__VA_ARGS__)

#endif // !_Console_hpp_

// Console.hpp ends here.
