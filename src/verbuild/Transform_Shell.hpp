//
// Transform_Shell.hpp --- Shell script transform interface.
//
// Copyright (c) 2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    24 Nov 2017 00:26:00
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
 * @file Transform_Shell.hpp
 * @author Paul Ward
 * @brief Shell script transform interface.
 */

#pragma once
#ifndef _Transform_Shell_hpp_
#define _Transform_Shell_hpp_

#include "Transform.hpp"

#define SHELL_KEY    "shell"
#define SHELL_PRETTY "Shell Script"

class ShellTransform
  : public Transform
{
private:
  std::string name_ = SHELL_PRETTY;

public:
  bool read(VersionInfo &) { return true; }
  bool write(VersionInfo &) { return true; }
};

static const bool registered_shell_transform = 
  get_transform_factory().register_transform(
    SHELL_KEY,
    SHELL_PRETTY,
    create_transform<ShellTransform>
  );

#endif // !_Transform_Shell_hpp_

// Transform_Shell.hpp ends here.
