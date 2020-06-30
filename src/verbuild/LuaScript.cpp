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
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>

#include <boost/regex.hpp>

static
int
findfield(lua_State* L, int objidx, int level)
{
  if (level == 0 || !lua_istable(L, -1)) {
    return 0;  /* not found */
  }

  lua_pushnil(L);                         /* start 'next' loop */
  while (lua_next(L, -2)) {               /* for each pair in table */
    if (lua_type(L, -2) == LUA_TSTRING) { /* ignore non-string keys */
      if (lua_rawequal(L, objidx, -1)) {  /* found object? */
        lua_pop(L, 1);                    /* remove value (but keep name) */
        return 1;
      } else if (findfield(L, objidx, level - 1)) { /* try recursively */
        /* stack: lib_name, lib_table, field_name (top) */
        lua_pushliteral(L, ".");        /* place '.' between the two names */
        lua_replace(L, -3);             /* (in the slot occupied by table) */
        lua_concat(L, 3);               /* lib_name.field_name */
        return 1;
      }
    }

    lua_pop(L, 1);                      /* remove value */
  }

  return 0;                             /* not found */
}

static
int
pushglobalfuncname(lua_State* L, lua_Debug* ar)
{
  int top = lua_gettop(L);
  lua_getinfo(L, "f", ar);              /* push function */
  lua_getfield(L, LUA_REGISTRYINDEX, LUA_LOADED_TABLE);

  if (findfield(L, top + 1, 2)) {
    const char* name = lua_tostring(L, -1);

    if (strncmp(name, LUA_GNAME ".", 3) == 0) { /* name start with '_G.'? */
      lua_pushstring(L, name + 3);              /* push name without prefix */
      lua_remove(L, -2);                        /* remove original name */
    }

    lua_copy(L, -1, top + 1);          /* copy name to proper place */
    lua_settop(L, top + 1);            /* remove table "loaded" and name copy */

    return 1;
  } else {
    lua_settop(L, top);                 /* remove function and global table */

    return 0;
  }
}

struct LuaStackResult
{
  std::string filename;
  int         lineNo;
  std::string function;
};

static
LuaStackResult
GetStackTrace(lua_State* state)
{
  LuaStackResult ret;
  lua_Debug      ar;
  int            top = lua_gettop(state);

  lua_getstack(state, 1, &ar);
  lua_getinfo(state, "Slnt", &ar);

  if (pushglobalfuncname(state, &ar)) {
    ret.function = std::string(lua_tostring(state, -1));
    lua_remove(state, -2);
  } else if (*ar.namewhat != '\0') {
    std::stringstream str;

    str << ar.namewhat << " '" << ar.name << "'";
    ret.function = str.str();
  } else if (*ar.what == 'm') {
    ret.function = "main chunk";
  } else if (*ar.what != 'C') {
    std::stringstream str;

    str << ar.short_src << ":" << ar.linedefined;
    ret.function = str.str();
  } else {
    ret.function = "?";
  }

  ret.lineNo   = ar.currentline;
  ret.filename = ar.short_src;

  return ret;
}

static
int
ExceptionHandler(lua_State*                           L,
                 sol::optional<const std::exception&> maybe_exception,
                 sol::string_view                     description)
{
  LuaStackResult stack = GetStackTrace(L);
  std::stringstream msg;
  
  msg << "Exception from Lua";

  if (maybe_exception) {
    const std::exception& ex = *maybe_exception;

    msg << ": " << ex.what();
  } else {
    msg << ": ";
    msg.write(description.data(), description.size());
  }

  Console()
    .error(stack.filename.c_str(), stack.lineNo, stack.function.c_str())
    .write(msg.str().c_str());


  return sol::stack::push(L, description);
}

static
void
DebugSay(int         level,
         std::string file,
         int         line,
         std::string caller,
         std::string msg)
{
  Console()
    .debug(level, file.c_str(), line, caller.c_str())
    .write(msg);
}

static
std::vector<std::string>
MatchByRegex(std::string str, std::string re, sol::table fields)
{
  boost::regex             rgx;
  boost::smatch            matches;
  std::vector<std::string> ret;
  std::vector<int>         want;

  DSAY(DEBUG_HIGH, "Lua called MatchByRegex");

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
  DSAY(DEBUG_HIGH, "Setting up Lua class bindings");

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

  DSAY(DEBUG_HIGH, "Constructing LuaScript");

  _state.open_libraries(sol::lib::base);

  _state.set("success",          false);
  _state.set("modinfo",          LuaInfo());
  _state.set("version",          VersionInfo());
  _state.set("buffer",           "");
  _state.set("verbuild_version", VERSION_STRING);

  _state.set_exception_handler(&ExceptionHandler);
  
  _state.set_function("match", &MatchByRegex);

  _state.set_function("debug", [](sol::variadic_args va) {
      lua_State*        L   = va.lua_state();
      lua_Debug         ar;
      int               top = lua_gettop(L);
      std::string       fname;
      std::stringstream msg;

      for (std::string arg : va) {
        msg << arg;
      }

      lua_getstack(L, 1, &ar);
      lua_getinfo(L, "Slnt", &ar);

      if (pushglobalfuncname(L, &ar)) {
        fname = std::string(lua_tostring(L, -1));
        lua_remove(L, -2);  /* remove name */
      } else if (*ar.namewhat != '\0') {
        std::stringstream str;

        str << ar.namewhat << " '" << ar.name << "'";
        fname = str.str();
      } else if (*ar.what == 'm') {
        fname = "main chunk";
      } else if (*ar.what != 'C') {
        std::stringstream str;

        str << ar.short_src << ":" << ar.linedefined;
        fname = str.str();
      } else {
        fname = "?";
      }

      lua_settop(L, top);
      
      DebugSay(1, std::string(ar.short_src), ar.currentline, fname, msg.str());
    });


  _state.set_function("diebitch", []() { throw std::runtime_error("Go die"); });

  LuaClassBindings(_state);
}

void
LuaScript::LoadFile(std::string filepath)
{
  try {
    _state.script_file(filepath);
  } catch (sol::error& e) {
    std::cout << "HANDLE " << e.what();
  } catch (std::exception& e) {
    std::cout << "IGNORE " << e.what();
  }
}

void
LuaScript::Parse()
{
  sol::protected_function parse = _state["parse"];

  DSAY(DEBUG_HIGH, "Lua invoking Parse()");

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

  DSAY(DEBUG_HIGH, "Lua invoking Info()");

  if (info.valid()) {
    auto res = info();

    _info = _state["modinfo"];
  }
}

// LuaScript.cpp ends here.
