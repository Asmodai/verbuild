//
// bitmask.hpp --- Bitmask hacks for scoped enums.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    21 Nov 2017 23:46:59
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
 * @file bitmask.hpp
 * @author Paul Ward
 * @brief Bitmask hacks for scoped enums.
 */

#pragma once
#ifndef _bitmask_hpp_
#define _bitmask_hpp_

#include "Support.hpp"

#include <type_traits>

template <typename Enum>
struct EnableBitMaskOperators
{
  static const bool enable = false;
};

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator&(Enum l, Enum r)
{
  static_assert(std::is_enum<Enum>::value, "Not an enum type");

  using underlaying = typename std::underlying_type<Enum>::type;

  return static_cast<Enum>(
    static_cast<underlaying>(l) & static_cast<underlaying>(r)
  );
}

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator|(Enum l, Enum r)
{
  static_assert(std::is_enum<Enum>::value, "Not an enum type");

  using underlaying = typename std::underlying_type<Enum>::type;

  return static_cast<Enum>(
    static_cast<underlaying>(l) | static_cast<underlaying>(r)
  );
}

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator^(Enum l, Enum r)
{
  static_assert(std::is_enum<Enum>::value, "Not an enum type");

  using underlaying = typename std::underlying_type<Enum>::type;

  return static_cast<Enum>(
    static_cast<underlaying>(l) ^ static_cast<underlaying>(r)
  );
}

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator~(Enum x)
{
  static_assert(std::is_enum<Enum>::value, "Not an enum type");

  using underlaying = typename std::underlying_type<Enum>::type;

  return static_cast<Enum>(~static_cast<underlaying>(x));
}

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type &
operator&=(Enum &l, Enum r)
{
  static_assert(std::is_enum<Enum>::value, "Not an enum type");

  l = l & r;

  return l;
}

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type &
operator|=(Enum &l, Enum r)
{
  static_assert(std::is_enum<Enum>::value, "Not an enum type");

  l = l | r;

  return l;
}

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type &
operator^=(Enum &l, Enum r)
{
  static_assert(std::is_enum<Enum>::value, "Not an enum type");

  l = l ^ r;

  return l;
}

# define ENABLE_BITMASK_OPS(__e)       \
  template<>                           \
  struct EnableBitMaskOperators<__e> { \
    static const bool enable = true;   \
  };

#endif // !_bitmask_hpp_

// bitmask.hpp ends here.
