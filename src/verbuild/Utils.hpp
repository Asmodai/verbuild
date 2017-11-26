//
// Utils.hpp --- Handy utilities.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    22 Nov 2017 00:15:39
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
 * @file Utils.hpp
 * @author Paul Ward
 * @brief Handy utilities.
 */

#pragma once
#ifndef _Utils_hpp_
#define _Utils_hpp_

#include "Support.hpp"

#include <string>
#include <vector>

#include <boost/any.hpp>

typedef std::vector<std::string> StringVector;
typedef StringVector::iterator   StringVecIterator;

typedef std::pair<std::string, std::string> ListPair;
typedef std::vector<ListPair>               ListPairVector;
typedef ListPairVector::iterator            ListPairVecIterator;

void ltrim(std::string &);
void rtrim(std::string &);
void trim(std::string &);

std::string ltrim_copy(std::string);
std::string rtrim_copy(std::string);
std::string trim_copy(std::string);

void delete_whitespace(std::string &);
void delete_whitespace(std::string &);

std::string delete_whitespace_copy(std::string);
std::string delete_whitespace_copy(std::string);

void downcase(std::string &);
void upcase(std::string &);

std::string downcase_copy(std::string);
std::string upcase_copy(std::string);

uint32_t safe_stoi(const std::string &, size_t * = 0, int = 10);

#endif // !_Utils_hpp_

// Utils.hpp ends here.
