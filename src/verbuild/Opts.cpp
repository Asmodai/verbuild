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

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/program_options.hpp>

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <ostream>
#include <cstdlib>

using namespace std;

namespace po   = boost::program_options;
namespace date = boost::gregorian;

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
      "Version number format string.\n\n"
      "This string represents how a version will be incremented.  "
      "The fields are:\n"
      "    <major>.<minor>.<build>.<patch>\n\n"
      "The options available are:\n"
      "    *   - Leave field as is.\n"
      "    +   - Increment field.\n\n"
      "If this flag is not specified, then the default will increment the "
      "build field only.");
}

static
void
generate_debug(po::options_description &desc)
{
  desc.add_options()
    ("debug,D",
     po::value<int>()
       ->default_value(0)
       ->implicit_value(1)
       ->value_name("level"),
     "When set, debugging messages will be shown.  The higher the level, "
     "the more verbose the debugging.\n\n"
     "If this flag is given with no argument, the level is set to 1; "
     "otherwise the level is set to the given value.\n\n"
     "If the flag is not given, the level defaults to 0.\n\n"
     "This flag does nothing if verbuild was built in debug mode.");
}

static
void
generate_misc(po::options_description &desc)
{
  desc.add_options()
    ("help,h",
     "Show this help message.")
    ("version,v",
     "Show program version.")
    ("verbose,V",
     "Enables verbose output, which will result in various "
     "information being displayed when the program runs");
}

Opts::Opts()
{}

Opts::~Opts()
{}

void
Opts::parse(int argc, char **argv)
{
  date::date today(date::day_clock::local_day());

  desc_.add_options()
    ("output,o",
     po::value<string>(),
     "File containing version information.")
    ("year,y",
     po::value<int>()
       ->default_value(1970)
       ->implicit_value(today.year())
       ->value_name("year"),
     "The year used for calendar offset calculations.\n\n"
     "If this flag is given with no argument, the year is set "
     "to the current year; otherwise the year is set to the "
     "given year.\n\n"
     "If the flag is not given, then the year is set to 1970.")
    ("increment,i",
     po::value<int>(),
     "Type of increment to use.")
    ("create,c",
     "If enabled, verbuild will create the output file if it "
     "does not exist.\n\n"
     "If this flag is not enabled, verbuild will exit with a fatal error "
     "if the output file does not exist.")
    ("transform,t",
     "Select a transform to use when writing version information.\n\n"
     "This allows you to create files for use with other languages "
     "besides C and C++.")
    ("groups,g",
     "Select which groups to write.\n\n"
     "Each file is made up of a few groups that are used for different "
     "purposes, such as a structure, preprocessor definitions, or "
     "comments that can be parsed by tools like Doxygen.")
    ("prefix,p",
     "A string that is prepended to symbols created by the transform "
     "module.");

  generate_misc(desc_);
  generate_debug(desc_);
  generate_format_string(desc_);

  try {
    po::store(po::parse_command_line(argc, argv, desc_), vmap_);
    po::notify(vmap_);
  }
  catch (std::exception &e) {
    FATAL(e.what());
    exit(EXIT_FAILURE);
  }
  catch (...) {
    FATAL("Unknown error!");
    exit(EXIT_FAILURE);
  }

  if (vmap_.count("help")) {
    std::cout << desc_ << std::endl;
    exit(EXIT_FAILURE);
  }

  if (vmap_.count("verbose")) {
    set_verbose(true);
    LSAY("Verbose mode enabled");
  }

  if (vmap_.count("format")) {
    IncrModeParser format = vmap_["format"].as<IncrModeParser>();
    LSAY("Format set to:", format);
    incr_mode_ = format.get_mode();
  } else {
    FATAL("No output formatter was specified.");
  }

  if (vmap_.count("year")) {
    int year = vmap_["year"].as<int>();

    if (year < 1970) {
      FATAL("Base year must be 1970 or greater.");
      exit(EXIT_FAILURE);
    }
    LSAY("Base year set to:", year);
    base_year_ = year;
  }

  ListPairVector lpv;

  lpv.push_back(ListPair("Wooties", "Nope"));
  lpv.push_back(ListPair("Isn't this great", "Yeah, whatever"));
  lpv.push_back(ListPair("Nice", "Are you still here?"));

  Console(&std::cout).write_pairs(lpv);
}

// Opts.cpp ends here.
