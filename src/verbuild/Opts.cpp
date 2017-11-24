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
#include "IncrTypeParser.hpp"
#include "TransformParser.hpp"
#include "GroupsParser.hpp"

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

static const char *program_name;

void
set_program_name(const char *name)
{
  program_name = name;
}

static
void
generate_info(po::options_description &desc)
{
  desc.add_options()
    ("list-groups",
     "List all available groups for use with the `groups' option.")
    ("list-increments",
     "List all available increments for use with the `increment' option.")
    ("list-transforms",
     "List all available transforms for use with the `transform' option.");
}

static
void
generate_transform(po::options_description &desc)
{
  desc.add_options()
    ("transform,t",
     po::value<TransformParser>()
       ->default_value(TransformParser("c"))
       ->value_name("transform"),
     "Select a transform to use when writing version information.\n\n"
     "This allows you to create files for use with other languages "
     "besides C and C++.")
    ("prefix,p",
     po::value<string>()
       ->default_value("")
       ->implicit_value("")
       ->value_name("prefix"),
     "A string that is prepended to symbols created by the transform "
     "module.");
}

static
void
generate_increment(po::options_description &desc)
{
  date::date today(date::day_clock::local_day());

  desc.add_options()
    ("format,f",
      po::value<IncrModeParser>()
        ->default_value(IncrModeParser("*.*.+.*"))
        ->value_name("format"),
      "Version number format string.\n\n"
      "This string represents how a version will be incremented.  "
      "The fields are:\n"
      "    <major>.<minor>.<build>.<patch>\n\n"
      "The options available are:\n"
      "    *   - Leave field as is.\n"
      "    +   - Increment field.\n"
      "   num  - Literal value.\n\n"
      "If this flag is not specified, then the default will increment the "
      "build field only.")
    ("increment,i",
     po::value<IncrTypeParser>()
       ->default_value(IncrTypeParser("simple"))
       ->value_name("type"),
     "Type of increment to use.")
    ("year,y",
     po::value<int>()
       ->default_value(1970)
       ->implicit_value(today.year())
       ->value_name("year"),
     "The year used for calendar offset calculations.\n\n"
     "If this flag is given with no argument, the year is set "
     "to the current year; otherwise the year is set to the "
     "given year.\n\n"
     "If the flag is not given, then the year is set to 1970.");
}

static
void
generate_output(po::options_description &desc)
{
  desc.add_options()
    ("create,c",
      "If enabled, verbuild will create the output file if it "
      "does not exist.\n\n"
      "If this flag is not enabled, verbuild will exit with a fatal error "
      "if the output file does not exist.")
    ("groups,g",
     po::value<GroupsParser>()
       ->default_value(GroupsParser("basic"))
       ->value_name("groups"),
     "Select which groups to write.\n\n"
     "Each file is made up of a few groups that are used for different "
     "purposes, such as a structure, preprocessor definitions, or "
     "comments that can be parsed by tools like Doxygen.")
    ("output,o",
     po::value<string>()
       ->value_name("file"),
     "File containing version information.");
}

static
void
generate_debug(po::options_description &desc)
{
  desc.add_options()
    ("verbose,V",
      "Enables verbose output, which will result in various "
      "information being displayed when the program runs")
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
   "Show program version.");
}

Opts::Opts()
{
  po::options_description general("General options");
  po::options_description debug("Debug options");
  po::options_description output("Output options");
  po::options_description increment("Increment options");
  po::options_description transform("Transform options");
  po::options_description info("Information options");

  generate_misc(general);
  generate_debug(debug);
  generate_output(output);
  generate_increment(increment);
  generate_transform(transform);
  generate_info(info);

  desc_.add(general);
  desc_.add(increment);
  desc_.add(transform);
  desc_.add(output);
  desc_.add(info);
  desc_.add(debug);
}

Opts::~Opts()
{}

void
Opts::parse(int argc, char **argv)
{
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
    show_help();
  }

  if (vmap_.count("list-transforms")) {
    show_list_transforms();
  }

  if (vmap_.count("list-increments")) {
    show_list_increments();
  }

  if (vmap_.count("list-groups")) {
    show_list_groups();
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
    exit(EXIT_FAILURE);
  }

  if (vmap_.count("increment")) {
    IncrTypeParser incr = vmap_["increment"].as<IncrTypeParser>();
    LSAY("Increment type set to:", incr);
    incr_type_ = incr.get_type();
  } else {
    FATAL("No increment type was specified.");
    exit(EXIT_FAILURE);
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

  if (vmap_.count("transform")) {
    TransformParser transform = vmap_["transform"].as<TransformParser>();
    LSAY("Transform set to:", transform);
    transform_ = transform.to_string();
  } else {
    FATAL("No transform was specified.");
    exit(EXIT_FAILURE);
  }

  if (vmap_.count("prefix")) {
    string tmp = vmap_["prefix"].as<string>();

    if (tmp.length() > 0) {
      prefix_.assign(tmp);
      delete_whitespace(prefix_);
      LSAY("Prefix set to:", prefix_);
    }
  }

  if (vmap_.count("create")) {
    LSAY("Will create file if it does not exist.");
    create_ = true;
  } else {
    LSAY("Will not create file if it does not exist.");
    create_ = false;
  }
}

void
Opts::show_help() const
{
  cout << "Usage: " << program_name << " [OPTION]...\n"
       << "Version number incrementing and build number tool.\n"
       << desc_ << endl;

  exit(EXIT_FAILURE);
}

void
Opts::show_list_transforms() const
{
  ListPairVector lpv;
  cout << "Available transforms:" << endl;

  for (auto it = TRANSFORM_BEGIN(); it != TRANSFORM_END(); it++) {
    lpv.push_back(ListPair(it->first, it->second));
  }

  Console(&std::cout).write_pairs(lpv, 4);

  exit(EXIT_SUCCESS);
}

void
Opts::show_list_increments() const
{
  IncrTypeParser parser;

  cout << "Available increment types:" << endl;

  for (auto &it : parser.allowed_values()) {
    cout << "    " << it << endl;
  }

  exit(EXIT_SUCCESS);
}

void
Opts::show_list_groups() const
{
  GroupsParser parser;

  cout << "Available output groups:" << endl;

  for (auto &it : parser.allowed_values()) {
    cout << "    " << it << endl;
  }

  exit(EXIT_SUCCESS);
}

// Opts.cpp ends here.
