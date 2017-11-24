//
// Transform.cpp --- Transform base class implementation.
//
// Copyright (c) 2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    23 Nov 2017 22:36:24
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
 * @file Transform.cpp
 * @author Paul Ward
 * @brief Transform base class implementation.
 */

#include "Transform.hpp"

#include <utility>

using namespace std;

Transform::Transform()
{}

Transform::~Transform()
{}

const string &
Transform::get_name() const
{
  return name_;
}

const OutputGroups
Transform::get_mode() const
{
  return mode_;
}

void
Transform::set_mode(const OutputGroups mode)
{
  mode_ = mode;
}

const string &
Transform::get_filename() const
{
  return filename_;
}

void
Transform::set_filename(const string &val)
{
  filename_ = val;
}

const string &
Transform::get_prefix() const
{
  return prefix_;
}

void
Transform::set_prefix(const string &val)
{
  prefix_ = val;
}

bool
Transform::read(VersionInfo &)
{
  throw runtime_error("Not implemented");
}

bool
Transform::write(VersionInfo &)
{
  throw runtime_error("Not implemented");
}


bool
TransformFactory::register_transform(const std::string &key,
                                     const std::string &pretty,
                                     const Builder     &fn)
{
  bool ok;

  ok = fns_.insert(std::make_pair(key, fn)).second;
  ok = ok && names_.insert(std::make_pair(key, pretty)).second;

  return ok;
}

Transform *
TransformFactory::build(const std::string &key) const
{
  auto it = fns_.find(key);

  DSAY(DEBUG_HIGH, "Looking up build function for", key);

  if (it == fns_.end()) {
    DSAY(DEBUG_HIGH, "Cannot find build function for", key);
    return nullptr;
  }

  DSAY(DEBUG_HIGH, "Returning build function for", key);
  return (it->second)();
}

TransformFactory::FnMapIterator
TransformFactory::builder_find(const std::string &key)
{
  return fns_.find(key);
}

TransformFactory::FnMapIterator
TransformFactory::builder_begin()
{
  return fns_.begin();
}

TransformFactory::FnMapIterator
TransformFactory::builder_end()
{
  return fns_.end();
}

TransformFactory::StringMapIterator
TransformFactory::find(const std::string &key)
{
  return names_.find(key);
}

TransformFactory::StringMapIterator
TransformFactory::begin()
{
  return names_.begin();
}

TransformFactory::StringMapIterator
TransformFactory::end()
{
  return names_.end();
}

static const std::string not_found = "not found";

const std::string &
TransformFactory::get_pretty(const std::string &key) const
{
  auto it = names_.find(key);

  DSAY(DEBUG_HIGH, "Looking up pretty name for", key);

  if (it == names_.end()) {
    DSAY(DEBUG_HIGH, "Cannot find pretty name for", key);
    return not_found;
  }

  DSAY(DEBUG_HIGH, "Returning pretty name for", key);
  return it->second;
}

TransformFactory &
get_transform_factory()
{
  static TransformFactory factory;

  return factory;
}

// Transform.cpp ends here.
