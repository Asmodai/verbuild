//
// main.cpp --- Main function.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    01 Jun 2013 09:12:33
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
 * @file main.cpp
 * @author Paul Ward
 * @brief Main function.
 */
 
#include "Console.hpp"
#include "Opts.hpp"
#include "Enums.hpp"

#include <cstdlib>

#include "VersionInfo.hpp"
#include "version.hpp"
#include "Enums.hpp"

#include "Transform_C.hpp"
#include "Transform_Shell.hpp"

#ifdef WITH_FLTK
# include <FL/fl.h>
#endif

int
main(int argc, char **argv)
{
  Opts *opts = new Opts();

  set_program_name(argv[0]);

  set_verbose(false);

#ifdef WITH_FLTK
  DSAY(DEBUG_EVERYTHING, "Using FLTK!");
#endif

  opts->parse(argc, argv);
  opts->print_config();

  Transform *transform = GET_TRANSFORM_CREATE(opts->get_transform());
  VersionInfo test;
  std::string fname(opts->get_filename());
  bool res = transform->read(test, fname);

  if (res) {
    test.set_increment_type(opts->get_increment_type());

    if (test.get_base_year() != opts->get_base_year()) {
      test.set_base_year(opts->get_base_year());
    }

    test.increment(opts->get_increment_mode());
    OK("Version:", test);
    std::cout << "Base year was: " << test.get_base_year() << std::endl;

    transform->write(test, fname);
  } else {
    FATAL("Nope");
  }

#if PLATFORM_EQ(PLATFORM_WINDOWS)
  ::getchar();
#endif

  /*
  VersionInfo bydate(1, 2, 20171121, 0, 2017, IncrementType::ByDate);
  VersionInfo bymonth(1, 2, 1121, 0, 2017, IncrementType::ByMonths);
  VersionInfo byyear(1, 2, 41121, 0, 2013, IncrementType::ByYears);

  //vi.increment(IncrementMode::Build);

  std::cout << "By Date:  " << bydate.to_date()  << " - " << bydate  << std::endl
            << "By Month: " << bymonth.to_date() << " - " << bymonth << std::endl
            << "By Year:  " << byyear.to_date()  << " - " << byyear  << std::endl;

  bydate.increment(IncrementMode::Build);
  bymonth.increment(IncrementMode::Build);
  byyear.increment(IncrementMode::Build);

  std::cout << "By Date:  " << bydate.to_date() << " - " << bydate << std::endl
    << "By Month: " << bymonth.to_date() << " - " << bymonth << std::endl
    << "By Year:  " << byyear.to_date() << " - " << byyear << std::endl;
    */

  return EXIT_SUCCESS;
}

// main.cpp ends here.
