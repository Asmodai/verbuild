//
// VersionInfo.hpp --- Version information class.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    29 May 2013 02:13:55
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

#pragma once
#ifndef __VersionInfo_hpp__
#define __VersionInfo_hpp__

#include "Support.hpp"
#include "Console.hpp"
#include "Enums.hpp"

#include <string>

#include <boost/date_time/gregorian/gregorian.hpp>

namespace date = boost::gregorian;

/**
 * @file VersionInfo.hpp
 * @author Paul Ward
 * @brief Version information class.
 */

class VersionInfo
{
private:
  std::uint32_t major_;
  std::uint32_t minor_;
  std::uint32_t build_;
  std::uint32_t patch_;
  std::uint32_t base_year_;
  IncrementType incr_type_;
  bool          overflow_;

public:
  VersionInfo();
  ~VersionInfo();

  VersionInfo(const std::uint32_t,      // major
              const std::uint32_t,      // minor
              const std::uint32_t,      // build
              const std::uint32_t,      // patch
              const std::uint32_t,      // base year
              IncrementType);

  const std::uint32_t &get_major() const;
  const std::uint32_t &get_minor() const;
  const std::uint32_t &get_build() const;
  const std::uint32_t &get_patch() const;
  const std::uint32_t &get_base_year() const;
  const IncrementType &get_increment_type() const;
  const bool          &get_overflow() const;

  void set_major(const std::uint32_t);
  void set_minor(const std::uint32_t);
  void set_build(const std::uint32_t);
  void set_patch(const std::uint32_t);
  void set_base_year(const std::uint32_t);
  void set_increment_type(const IncrementType);
  void set_overflow(const bool);

  void increment(const IncrementMode);

  std::string to_string() const;
  date::date  to_date() const;

  bool operator==(const VersionInfo &);
  bool operator!=(const VersionInfo &);

  friend std::ostream &operator<<(std::ostream &, const VersionInfo &);

private:
  std::uint32_t incr(const std::uint32_t) const;
  std::uint32_t add(const std::uint32_t, const std::uint32_t) const;
  void          perform();
};

#endif // !__VersionInfo_hpp__

// VersionInfo.hpp ends here.
