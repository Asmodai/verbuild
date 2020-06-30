//
// LuaScript.hpp --- Lua scripting interface.
//
// Copyright (c) 2020 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    30 Jun 2020 17:29:32
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
 * @file LuaScript.hpp
 * @author Paul Ward
 * @brief Lua scripting interface.
 */

#pragma once
#ifndef _LuaScript_hpp_
#define _LuaScript_hpp_

#include <string>

#define SOL_PRINT_ERRORS   0
#include <sol/sol.hpp>
#undef SOL_PRINT_ERRORS

#include "VersionInfo.hpp"

struct LuaInfo {

private:
  std::string _transform;
  std::string _name;
  std::string _author;

public:
  LuaInfo()
    : _transform(""),
      _name("Unknown"),
      _author("Unknown")
  {}

  void print() const;

  std::string get_transform() const { return _transform; }
  std::string get_name()      const { return _name;      }
  std::string get_author()    const { return _author;    }

  void set_transform(std::string value) { _transform = value; }
  void set_name(std::string value)      { _name = value;      }
  void set_author(std::string value)    { _author = value;    }
};

class LuaScript
{

private:
  sol::state  _state;
  LuaInfo     _info;
  VersionInfo _version;
  bool        _success;

public:
  LuaScript();

  LuaScript(const LuaScript&) = delete;

  ~LuaScript()
  {}

  const LuaInfo     GetInfo()    const { return _info;    }
  const VersionInfo GetVersion() const { return _version; }

  void LoadFile(std::string filepath);

  void Info();
  void Parse();
  void Parse(const std::string&);

}; // class LuaScript

#endif // !_LuaScript_hpp_

// LuaScript.hpp ends here.
