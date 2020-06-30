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
#include "Config.hpp"

#include "Transform_C.hpp"

int
main(int argc, char **argv)
{
  Config  conf;
  Opts   *opts = new Opts();

  set_program_name(argv[0]);
  set_verbose(false);

  opts->parse(conf, argc, argv);
  if (get_verbose()) {
    LSAY("Configuration:");
    conf.print();
  }

  Transform   *transform = GET_TRANSFORM_CREATE(conf.transform);
  VersionInfo  vi;

  transform->set_config(conf);
  if (transform->read(vi)) {
    vi.set_increment_type(conf.incr_type);
    vi.set_base_year(conf.base_year);

    vi.increment(conf.incr_mode);
    transform->write(vi);

    OK("Version incremented to:", vi);
  } else {
    if (conf.create || conf.filename.length() == 0) {
      vi.set_base_year(conf.base_year);
      vi.set_major(0);
      vi.set_minor(0);
      vi.set_build(0);
      vi.set_patch(0);
      vi.increment(conf.incr_mode);
      transform->write(vi);

      OK("Version incremented to:", vi);
    } else {
      FATAL("Could not open", conf.filename, "for reading.");
      FATAL("Did you forget to specify `-c'?");
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}

// main.cpp ends here.
