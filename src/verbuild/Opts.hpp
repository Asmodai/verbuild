//
// Opts.hpp --- Program options.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    22 Nov 2017 00:10:55
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
 * @file Opts.hpp
 * @author Paul Ward
 * @brief Program options..
 */

#pragma once
#ifndef _Opts_hpp_
#define _Opts_hpp_

#include "Support.hpp"
#include "Enums.hpp"
#include "Utils.hpp"
#include "IncrModeParser.hpp"

#include <string>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

class Opts
{
private:
  po::variables_map       vmap_;
  po::options_description desc_;

private:
  std::uint32_t base_year_;
  IncrementMode incr_mode_;

public:
  Opts();
  Opts(const Opts &) = delete;
  ~Opts();

  void parse(int, char **);

  const std::uint32_t  get_base_year() const;
  const IncrementMode &get_increment_mode() const;

private:
  void show_help() const;
};

#endif // !_Opts_hpp_

// Opts.hpp ends here.
