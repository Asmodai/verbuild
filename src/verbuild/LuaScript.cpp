//
// LuaScript.cpp --- Lua scripting interface.
//
// Copyright (c) 2020 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    30 Jun 2020 17:28:16
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
 * @file LuaScript.cpp
 * @author Paul Ward
 * @brief Lua scripting interface.
 */
 
#include "LuaScript.hpp"
#include "Console.hpp"
#include "Opts.hpp"
#include "version.hpp"

#include <string>
#include <vector>
#include <cstdlib>

#include <boost/regex.hpp>

static
std::vector<std::string>
MatchByRegex(std::string str, std::string re, sol::table fields)
{
  boost::regex             rgx;
  boost::smatch            matches;
  std::vector<std::string> ret;
  std::vector<int>         want;

  for (size_t idx = 0u; idx < fields.size(); idx++) {
    want.push_back(fields[idx + 1]);
  }

  rgx.set_expression(re);
  boost::regex_token_iterator<std::string::iterator> it{
    str.begin(),
    str.end(),
    rgx,
    want
  };
  boost::regex_token_iterator<std::string::iterator> end;

  while (it != end) {
    if (it->matched) {
      ret.push_back(*it);
    }

    *it++;
  }

  return ret;
}

void
LuaClassBindings(sol::state& state)
{
  state.new_usertype<LuaInfo>(
      "LuaInfo",
      "transform", sol::property(&LuaInfo::get_transform, &LuaInfo::set_transform),
      "name",      sol::property(&LuaInfo::get_name,      &LuaInfo::set_name),
      "author",    sol::property(&LuaInfo::get_author,    &LuaInfo::set_author)
  );

  state.new_usertype<VersionInfo>(
      "VersionInfo",
      "year",  sol::property(&VersionInfo::get_base_year, &VersionInfo::set_base_year),
      "major", sol::property(&VersionInfo::get_major,     &VersionInfo::set_major),
      "minor", sol::property(&VersionInfo::get_minor,     &VersionInfo::set_minor),
      "build", sol::property(&VersionInfo::get_build,     &VersionInfo::set_build),
      "patch", sol::property(&VersionInfo::get_patch,     &VersionInfo::set_patch)
  );
}

void
LuaInfo::print() const
{
    std::cout
      << "Transform: " << _transform
      << " - "         << _name
      << " ("          << _author << ")" << std::endl;
}

LuaScript::LuaScript()
{
  _state   = sol::state();
  _info    = LuaInfo();
  _version = VersionInfo();
  _success = false;

  _state.open_libraries(sol::lib::base);

  _state.set("success",          false);
  _state.set("modinfo",          LuaInfo());
  _state.set("version",          VersionInfo());
  _state.set("buffer",           "");
  _state.set("verbuild_version", VERSION_STRING);

  _state.set_function("match", &MatchByRegex);

  LuaClassBindings(_state);
}

void
LuaScript::LoadFile(std::string filepath)
{
  _state.script_file(filepath);
}

void
LuaScript::Parse()
{
  sol::protected_function parse = _state["parse"];

  if (parse.valid()) {
    auto res = parse();
    
    _version = _state["version"];
    _success  = _state["success"];

    return;
  }
  
  _state.set("success", false);
}

void
LuaScript::Parse(const std::string& buffer)
{
  _state.set("buffer", buffer);

  Parse();
}

void
LuaScript::Info()
{
  sol::protected_function info = _state["info"];

  if (info.valid()) {
    auto res = info();

    _info = _state["modinfo"];
  }
}

// LuaScript.cpp ends here.
