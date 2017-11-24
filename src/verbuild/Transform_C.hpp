//
// Transform_C.hpp --- C/C++ transform interface.
//
// Copyright (c) 2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    23 Nov 2017 23:02:15
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
 * @file Transform_C.hpp
 * @author Paul Ward
 * @brief C/C++ transform interface.
 */

#pragma once
#ifndef _Transform_C_hpp_
#define _Transform_C_hpp_

#include "Transform.hpp"

#define C_KEY    "c"
#define C_PRETTY "C/C++"

class CTransform
  : public Transform
{
private:
  std::string name_ = C_PRETTY;

public:
  bool read(VersionInfo &) { return true; }
  bool write(VersionInfo &) { return true; }
};

static const bool registered_c_transform =
  get_transform_factory().register_transform(
    C_KEY,
    C_PRETTY,
    create_transform<CTransform>
  );

#endif // !_Transform_C_hpp_

// Transform_C.hpp ends here.
