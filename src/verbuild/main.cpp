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


int
main(int argc, char **argv)
{
  Opts      *opts = new Opts();

  set_verbose(false);

  opts->parse(argc, argv);
  std::cout << "Starting verbuild " << _GIT_VERSION << std::endl;

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

  return EXIT_SUCCESS;
}

// main.cpp ends here.
