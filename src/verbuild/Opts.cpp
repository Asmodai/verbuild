//
// Opts.cpp --- Program options
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    22 Nov 2017 00:08:08
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
 * @file Opts.cpp
 * @author Paul Ward
 * @brief Program options
 */

#include "Support.hpp"
#include "Opts.hpp"
#include "Console.hpp"
#include "Enums.hpp"
#include "Utils.hpp"
#include "IncrModeParser.hpp"
#include "Settings.hpp"

#include <boost/program_options.hpp>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <ostream>
#include <cstdlib>

using namespace std;
namespace po = boost::program_options;

namespace Callbacks
{
  static
    void
    format_string_cb(const string &val)
  {
    LSAY("Got:", val);
    //throw new std::exception("No cheese.");
  }
}

static
void
generate_format_string(po::options_description &desc)
{
  desc.add_options()
    ("format,f",
      po::value<IncrModeParser>()
      ->default_value(IncrModeParser("*.*.+.*"))
      ->value_name("format")
      /*->notifier(Callbacks::format_string_cb)*/,
      "Version number format string.");
}

static
void
generate_misc(po::options_description &desc)
{
  desc.add_options()
    ("help,h", "Show this help message.")
    ("version,v", "Show program version.")
    ("verbose,V", "Show verbose output.");
}

Opts::Opts()
{}

Opts::~Opts()
{}

void
Opts::parse(int argc, char **argv)
{
  po::variables_map        vm;
  po::options_description  desc("VerBuild");
  Settings                *settings = new Settings();

  desc.add_options()
    ("output,o",
     po::value<string>(),
     "File containing version information.")
    ("base-year,y",
     po::value<int>()->default_value(1970),
     "The year the project was started.")
    ("increment,i",
     po::value<int>(),
     "Type of increment to use.");

  generate_misc(desc);
  generate_format_string(desc);

  try {
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
  }
  catch (std::exception &e) {
    FATAL(e.what());
    exit(EXIT_FAILURE);
  }
  catch (...) {
    FATAL("Unknown error!");
    exit(EXIT_FAILURE);
  }

  if (vm.count("help")) {
    std::cout << desc << std::endl;
    exit(EXIT_FAILURE);
  }

  if (vm.count("verbose")) {
    set_verbose(true);
    LSAY("Verbose mode enabled");
  }

  if (vm.count("format")) {
    IncrModeParser format = vm["format"].as<IncrModeParser>();
    LSAY("Format set to:", format);
    settings->set_increment_mode(format.get_mode());
  } else {
    FATAL("No output formatter was specified.");
  }

  if (vm.count("base-year")) {
    int year = vm["base-year"].as<int>();

    if (year < 1970) {
      FATAL("Base year must be 1970 or greater.");
      exit(EXIT_FAILURE);
    }
    LSAY("Base year set to:", year);
    settings->set_base_year(year);
  }

  std::cout << *settings << std::endl;
}

// Opts.cpp ends here.
