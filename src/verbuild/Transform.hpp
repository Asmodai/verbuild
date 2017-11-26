//
// Transform.hpp --- Transform base class.
//
// Copyright (c) 2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    23 Nov 2017 22:10:52
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
 * @file Transform.hpp
 * @author Paul Ward
 * @brief Transform base class.
 */

#pragma once
#ifndef _Transform_hpp_
#define _Transform_hpp_

#include "Enums.hpp"
#include "VersionInfo.hpp"
#include "Config.hpp"

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>
#include <map>
#include <functional>

class Transform
{
protected:
  std::string name_;
  std::string option_;
  Config      conf_;

public:
  Transform();
  virtual ~Transform();

  const std::string &get_name() const;

  const Config &get_config() const;
  void          set_config(Config &);

  bool read(VersionInfo &);
  bool write(VersionInfo &);

private:
  virtual bool read_impl(VersionInfo &, std::string &);
  virtual bool write_impl(VersionInfo &, std::stringstream &);
};

class TransformFactory
{
public:
  typedef std::function<Transform *()>       Builder;
  typedef std::map<std::string, Builder>     FnMap;
  typedef std::map<std::string, std::string> StringMap;
  typedef FnMap::iterator                    FnMapIterator;
  typedef StringMap::iterator                StringMapIterator;

private:
  FnMap     fns_;
  StringMap names_;

public:
  bool register_transform(const std::string &,
                          const std::string &,
                          const Builder     &);

  Transform *build(const std::string &) const;

  FnMapIterator builder_find(const std::string &);
  FnMapIterator builder_begin();
  FnMapIterator builder_end();

  StringMapIterator find(const std::string &);
  StringMapIterator begin();
  StringMapIterator end();

  const std::string &get_pretty(const std::string &) const;
};

template <typename DerivedT>
Transform *create_transform() { return new DerivedT(); }

TransformFactory &get_transform_factory();

#define GET_TRANSFORM_CREATE(__k) get_transform_factory().build(__k)
#define GET_TRANSFORM_PRETTY(__k) get_transform_factory().get_pretty(__k)

#define FIND_TRANSFORM_PRETTY(__k) get_transform_factory().find(__k)
#define TRANSFORM_BEGIN()          get_transform_factory().begin()
#define TRANSFORM_END()            get_transform_factory().end()

#define FIND_TRANSFORM_BUILDER(__k) get_transform_factory().builder_find(__k)
#define TRANSFORM_BUILDER_BEGIN()   get_transform_factory().builder_begin()
#define TRANSFORM_BUILDER_END()     get_transform_factory().builder_end()

#endif // !_Transform_hpp_

// Transform.hpp ends here.
