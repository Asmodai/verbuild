//
// Utils.cpp --- Handy utilities.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    22 Nov 2017 00:15:11
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
 * @file Utils.cpp
 * @author Paul Ward
 * @brief Handy utilities.
 */
 
#include "Utils.hpp"
#include "Console.hpp"

#include <sstream>
#include <iterator>
#include <algorithm>
#include <cstdlib>

using namespace std;

void
ltrim(string &s)
{
  s.erase(s.begin(),
          find_if(s.begin(),
                  s.end(),
                  [](int ch) {
                    return !::isspace(ch);
                  }
          )
  );
}

void
rtrim(string &s)
{
  s.erase(find_if(s.rbegin(),
                  s.rend(),
                  [](int ch) {
                    return !::isspace(ch);
                  }
          ).base(),
          s.end()
  );
}

void
trim(string &s)
{
  ltrim(s);
  rtrim(s);
}

void
delete_whitespace(string &s)
{
  s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
}

string
delete_whitespace_copy(string s)
{
  delete_whitespace(s);

  return s;
}

string
ltrim_copy(string s)
{
  ltrim(s);

  return s;
}

string
rtrim_copy(string s)
{
  rtrim(s);

  return s;
}

string
trim_copy(string s)
{
  trim(s);

  return s;
}

void
downcase(string &s)
{
  transform(s.begin(), s.end(), s.begin(), ::tolower);
}

void
upcase(string &s)
{
  transform(s.begin(), s.end(), s.begin(), ::toupper);
}

string
downcase_copy(string s)
{
  downcase(s);

  return s;
}

string
upcase_copy(string s)
{
  upcase(s);

  return s;
}

uint32_t
safe_stoi(const string &str,
          size_t       *pos,
          int           base)
{
  uint32_t res = 0;

  try
  {
    res = static_cast<uint32_t>(stoi(str));
  }
  catch (invalid_argument &e) {
    DSAY(DEBUG_HIGH, "Invalid argument: ", e.what());
    res = 0;
  }
  catch (out_of_range &) {
    DSAY(DEBUG_HIGH,
      "The given number is too large. "
      "Defaulting to 0.");
    res = 0;
  }
  catch (...) {
    DSAY(DEBUG_EVERYTHING, "Unhandled exception.");
    FATAL("Terminating.");
    exit(EXIT_FAILURE);
  }

  return res;
}

// Utils.cpp ends here.
