//
// Console.cpp --- Console utilities.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    21 Nov 2017 23:57:07
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
 * @file Console.cpp
 * @author Paul Ward
 * @brief Console utilities.
 */
 
#include "Console.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

using namespace std;

#define ANSI_LIGHT_RED     "\033[1;31m"
#define ANSI_LIGHT_GREEN   "\033[1;32m"
#define ANSI_YELLOW        "\033[1;33m"
#define ANSI_LIGHT_BLUE    "\033[1;34m"
#define ANSI_LIGHT_MAGENTA "\033[1;35m"
#define ANSI_LIGHT_CYAN    "\033[1;36m"
#define ANSI_WHITE         "\033[1;37m"
#define ANSI_NONE          "\033[0m"

static ostream nullout(nullptr);
static Console nullcon(&nullout);

bool verbose    = false;
int debug_level = 
#if defined(DEBUG)
    DEBUG_EVERYTHING
#else
    DEBUG_NONE
#endif
    ;

#if PLATFORM_EQ(PLATFORM_WINDOWS)
# define WIN32_LEAN_AND_MEAN
# include <windows.h>

static bool ansi_console_enabled = false;

static
void
enable_ansi_console()
{
  if (ansi_console_enabled) {
    return;
  }

  HANDLE out  = ::GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD  mode = 0;

  ::GetConsoleMode(out, &mode);
  mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  ::SetConsoleMode(out, mode);

  ansi_console_enabled = true;
}

#endif  // PLATFORM_WINDOWS

void
set_verbose(bool flag)
{
  verbose = flag;
}

bool
get_verbose()
{
  return verbose;
}

void
set_debug_level(int level)
{
  debug_level = level;
}

bool
debug_level_met(int level)
{
  return (debug_level > 0 &&
          (debug_level >= level || debug_level == DEBUG_EVERYTHING));
}


static
void
print_preamble(ostream *stm,
               const char   *color,
               const char   *prefix)
{
  *stm << ANSI_WHITE << "["
       << color << prefix
       << ANSI_WHITE << "]"
       << ANSI_NONE << " ";
}

Console::Console()
  : Console(&cerr)
{}

Console::Console(ostream *stm)
  : out_(stm)
{
#if PLATFORM_EQ(PLATFORM_WINDOWS)
  enable_ansi_console();
#endif
}

ostream *
Console::get_stream() const
{
  return out_;
}

void
Console::write_pairs(ListPairVector &pairs, size_t indent) const
{
  static size_t ansi_width = 0;

  size_t       max_width  = 0;
  size_t       elem_width = 0;
  stringstream ss;

  if (ansi_width == 0) {
    ansi_width = ::strlen(ANSI_WHITE) + ::strlen(ANSI_NONE) + 2;
  };

  for (auto &it : pairs) {
    elem_width = it.first.length() + ansi_width;

    if (elem_width > max_width) {
      max_width = elem_width;
    }
  }
  max_width++;

  for (auto &it : pairs) {
    elem_width = max_width - (it.first.length() + ansi_width);

    ss << string(indent, ' ')
       << ANSI_WHITE << it.first << ANSI_NONE << ":"
       << string(elem_width, ' ') << " "
       << it.second << "\n";
  }

  *out_ << ss.str();
}

Console &
Console::log()
{
  if (!verbose) {
    return nullcon;
  }

  print_preamble(out_, ANSI_LIGHT_GREEN, "LOG");

  return *this;
}

Console &
Console::debug(const int   level,
               const char *file,
               const int   line,
               const char *function)
{
  if (!debug_level_met(level)) {
    return nullcon;
  }

  print_preamble(out_, ANSI_YELLOW, "DEBUG");
  *out_ << ANSI_WHITE << "[" << ANSI_LIGHT_CYAN
        << file << ":" << line
        << ANSI_WHITE << "]: ["
        << ANSI_LIGHT_BLUE << function << ANSI_WHITE << "]"
        << ANSI_NONE << " ";
  
  return *this;
}

Console &
Console::warn(const char *file,
              const int   line,
              const char *function)
{
  print_preamble(out_, ANSI_LIGHT_MAGENTA, "WARN");
  *out_ << ANSI_WHITE << "[" << ANSI_LIGHT_CYAN
        << file << ":" << line
        << ANSI_WHITE << "]: ["
        << ANSI_LIGHT_BLUE << function << ANSI_WHITE << "]"
        << ANSI_NONE << " ";

  return *this;
}

Console &
Console::error(const char *file,
               const int   line,
               const char *function)
{
  print_preamble(out_, ANSI_LIGHT_RED, "ERROR");
  *out_ << ANSI_WHITE << "[" << ANSI_LIGHT_CYAN
        << file << ":" << line
        << ANSI_WHITE << "]: ["
        << ANSI_LIGHT_BLUE << function << ANSI_WHITE << "]"
        << ANSI_NONE << " ";

  return *this;
}

Console &
Console::fatal()
{
  print_preamble(out_, ANSI_LIGHT_RED, "FATAL");

  return *this;
}

Console &
Console::ok()
{
  print_preamble(out_, ANSI_LIGHT_GREEN, "OK");

  return *this;
}

// Console.cpp ends here.
