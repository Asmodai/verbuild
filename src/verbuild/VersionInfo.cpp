//
// VersionInfo.cpp --- Version information implementation.
//
// Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    22 Nov 2017 05:49:55
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
 * @file VersionInfo.cpp
 * @author Paul Ward
 * @brief Version information implementation.
 */
 
#include "VersionInfo.hpp"
#include "Utils.hpp"

#include <climits>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <regex>

#include <boost/format.hpp>

using namespace std;
namespace       date = boost::gregorian;

VersionInfo::VersionInfo()
  : VersionInfo(0, 0, 0, 0, 0, IncrementType::Simple)
{}

VersionInfo::VersionInfo(const uint32_t major,
                         const uint32_t minor,
                         const uint32_t build     = 0,
                         const uint32_t patch     = 0,
                         const uint32_t baseyear  = 0,
                         const IncrementType type = IncrementType::Simple)
  : major_(major),
    minor_(minor),
    build_(build),
    patch_(patch),
    base_year_(baseyear),
    incr_type_(type)
{}

VersionInfo::~VersionInfo()
{}

const uint32_t &
VersionInfo::get_major() const
{
  return major_;
}

const uint32_t &
VersionInfo::get_minor() const
{
  return minor_;
}

const uint32_t &
VersionInfo::get_build() const
{
  return build_;
}

const uint32_t &
VersionInfo::get_patch() const
{
  return patch_;
}

const uint32_t &
VersionInfo::get_base_year() const
{
  return base_year_;
}

const IncrementType &
VersionInfo::get_increment_type() const
{
  return incr_type_;
}

void
VersionInfo::set_major(const uint32_t major)
{
  DSAY(DEBUG_HIGH, "Setting major to", major);
  major_ = major;
}

void
VersionInfo::set_minor(const uint32_t minor)
{
  DSAY(DEBUG_HIGH, "Setting minor to", minor);
  minor_ = minor;
}

void
VersionInfo::set_build(const uint32_t build)
{
  DSAY(DEBUG_HIGH, "Setting build to", build);
  build_ = build;
}

void
VersionInfo::set_patch(const uint32_t patch)
{
  DSAY(DEBUG_HIGH, "Setting patch to", patch);
  patch_ = patch;
}

void
VersionInfo::set_base_year(const uint32_t year)
{
  DSAY(DEBUG_HIGH, "Setting base year to", year);
  base_year_ = year;
}

void
VersionInfo::set_increment_type(const IncrementType type)
{
  DSAY(DEBUG_HIGH, "Setting increment type to", type);
  incr_type_ = type;
}

void
VersionInfo::increment(const IncrementMode mode)
{
  DSAY(DEBUG_LOW, "Performing increment");

  if ((mode & IncrementMode::Major) == IncrementMode::Major) {
    major_ = incr(major_);
  }

  if ((mode & IncrementMode::Minor) == IncrementMode::Minor) {
    minor_ = incr(minor_);
  }

  if ((mode & IncrementMode::Build) == IncrementMode::Build) {
    perform();
  }

  if ((mode & IncrementMode::Patch) == IncrementMode::Patch) {
    patch_ = incr(patch_);
  }
}

string
VersionInfo::to_string() const
{
  stringstream ss;

  ss << major_ << "."
     << minor_ << "."
     << build_ << "."
     << patch_;

  return ss.str();
}

date::date
VersionInfo::to_date() const
{
  date::date result;

  DSAY(DEBUG_LOW, "Starting conversion to date.");

  if (build_ > 0 && base_year_ > 0) {
    switch (incr_type_) {
      case IncrementType::ByDate:
        DSAY(DEBUG_MEDIUM, "Treating build number as date.");
        {
          stringstream ss;

          ss << build_;

          DSAY(DEBUG_HIGH, "Generating date.");
          try {
            result = date::date(date::from_undelimited_string(ss.str()));
          }
          catch (date::bad_month &e) {
            ESAY("Bad month:", e.what());
            FATAL("Terminating.");
            exit(EXIT_FAILURE);
          }
          catch (date::bad_year &e) {
            ESAY("Bad year:", e.what());
            FATAL("Terminating.");
            exit(EXIT_FAILURE);
          }
          catch (date::bad_day_of_month &e) {
            ESAY("Bad day of month:", e.what());
            FATAL("Terminating.");
            exit(EXIT_FAILURE);
          }
          catch (exception &e) {
            ESAY("Caught unhandled exception:", e.what(), ". Internal name:", typeid(e).name());
            FATAL("Terminating.");
            exit(EXIT_FAILURE);
          }

        }
        break;

      case IncrementType::ByYears:
        DSAY(DEBUG_MEDIUM, "Treating build number as year offset.");
        {
          stringstream ss;
          uint32_t     dd      = 0;
          uint32_t     mm      = 0;
          uint32_t     yy      = 0;
          bool         ok      = true;
          bool         matched = false;
          string       str;

          ss << build_;
          str = ss.str();

          if (str.length() > 3) {
            regex  re("(\\d*)(\\d{2,2})(\\d{2,2})");
            smatch matches;

            matched = regex_match(str, matches, re);
            DSAY(DEBUG_HIGH, "Matched", matches.size(), "via regex.");

            if (matched && matches.size() == 4) {
              yy = static_cast<uint32_t>(safe_stoi(matches[1]));
              mm = static_cast<uint32_t>(safe_stoi(matches[2]));
              dd = static_cast<uint32_t>(safe_stoi(matches[3]));
              DSAY(DEBUG_VERYHIGH, "Years:", yy, " Months:", mm, " Days:", dd);
            } else {
              DSAY(DEBUG_VERYHIGH, "Regex failed to match.");
              ok = false;
            }
          } else {
            regex  re("(\\d{1,2})(\\d{2,2})");
            smatch matches;

            matched = regex_match(str, matches, re);
            DSAY(DEBUG_HIGH, "Matched", matches.size(), "via regex.");

            if (matched && matches.size() == 3) {
              yy = 0;
              mm = static_cast<uint32_t>(safe_stoi(matches[1]));
              dd = static_cast<uint32_t>(safe_stoi(matches[2]));
              DSAY(DEBUG_VERYHIGH, "Years:", yy, " Months:", mm, " Days:", dd);
            } else {
              DSAY(DEBUG_VERYHIGH, "Regex failed to match.");
              ok = false;
            }
          }

          if (ok) {
            DSAY(DEBUG_HIGH, "Generating date.");

            stringstream ss;

            ss << base_year_ + yy
               << setfill('0') << setw(2)
               << mm << dd;

            try {
              result = date::date(date::from_undelimited_string(ss.str()));
            }
            /* XXX MOAR HERE */
            catch (date::bad_day_of_month &e) {
              ESAY("Bad day of month:", e.what());
              FATAL("Terminating.");
              exit(EXIT_FAILURE);
            }
            catch (...) {
              ESAY("Caught unhandled exception.");
              FATAL("Terminating.");
              exit(EXIT_FAILURE);
            }
          }
        }
        break;

      case IncrementType::ByMonths:
        DSAY(DEBUG_MEDIUM, "Treating build number as month offset.");
        DSAY(DEBUG_HIGH, "Generating date.");

        try {
          result  = date::date(base_year_, 1, build_ % 100);
          result += date::months((build_ / 100) - 1);
        }
        /* XXX MOAR HERE */
        catch (date::bad_day_of_month &e) {
          ESAY("Bad day of month:", e.what());
          FATAL("Terminating.");
          exit(EXIT_FAILURE);
        }
        catch (...) {
          ESAY("Caught unhandled exception.");
          FATAL("Terminating.");
          exit(EXIT_FAILURE);
        }
        break;

      case IncrementType::Simple:
        result = date::day_clock::local_day();
        break;

      default:
        throw invalid_argument("Unhandled increment type");
    }
  }

  return result;
}

bool
VersionInfo::operator==(const VersionInfo &other)
{
  return (major_ == other.major_)
      && (minor_ == other.minor_)
      && (build_ == other.build_)
      && (patch_ == other.patch_);
}

bool
VersionInfo::operator!=(const VersionInfo &other)
{
  return (major_ != other.major_)
      || (minor_ != other.minor_)
      || (build_ != other.build_)
      || (patch_ != other.patch_);
}

uint32_t
VersionInfo::incr(const uint32_t lhs) const
{
  // This is just to be safe... 
  if ((UINT_MAX - 1) < lhs) {
    return UINT_MAX;
  }

  return lhs + 1;
}

uint32_t
VersionInfo::add(const uint32_t lhs, const uint32_t rhs) const
{
  // This is just to be safe...
  if ((UINT_MAX - rhs) < lhs) {
    return UINT_MAX;
  }

  return lhs + rhs;
}

void
VersionInfo::perform()
{
  switch (incr_type_) {
    case IncrementType::Simple:
      build_++;
      break;

    case IncrementType::ByMonths:
      DSAY(DEBUG_MEDIUM, "Incrementing by month offset.");
      if (base_year_ > 0) {
        date::date current(date::day_clock::local_day());

        build_ = add((current.year() - base_year_) * 12,
                     (int)current.month());
        build_ = add(build_ * 100, current.day());
        DSAY(DEBUG_VERYHIGH, "build now", build_);
      }
      break;

    case IncrementType::ByYears:
      DSAY(DEBUG_MEDIUM, "Incrementing by year offset.");
      {
        date::date   current(date::day_clock::local_day());
        stringstream ss;

        ss << current.year() - base_year_
           << setfill('0') << setw(2)
           << (int)current.month()      // Defaults to month name, see.
           << current.day();

        try {
          DSAY(DEBUG_VERYHIGH, "setting build to", ss.str());
          build_ = static_cast<uint32_t>(safe_stoi(ss.str()));
        }
        catch (invalid_argument &e) {
          ESAY("Invalid argument:", e.what());
          build_ = 0;
        }
        catch (out_of_range &e) {
          ESAY("Out of range:", e.what());
          build_ = 0;
        }
        catch (...) {
          ESAY("Caught unhandled exception.");
          FATAL("Terminating.");
          exit(EXIT_FAILURE);
        }
      }
      break;

    case IncrementType::ByDate:
      DSAY(DEBUG_MEDIUM, "Incrementing by date.");
      {
        date::date   current(date::day_clock::local_day());
        stringstream ss;

        ss << current.year()
           << setfill('0') << setw(2)
           << (int)current.month()      // Defaults to month, see.
           << current.day();

        try {
          DSAY(DEBUG_VERYHIGH, "setting build to", ss.str());
          build_ = static_cast<uint32_t>(safe_stoi(ss.str()));
        }
        catch (invalid_argument &e) {
          ESAY("Invalid argument:", e.what());
          build_ = 0;
        }
        catch (out_of_range &e) {
          ESAY("Out of range:", e.what());
          build_ = 0;
        }
        catch (...) {
          ESAY("Caught unhandled exception.");
          FATAL("Terminating.");
          exit(EXIT_FAILURE);
        }
      }
      break;

    default:
      throw invalid_argument("Unhandled increment type");
  }
}

ostream &
operator<<(ostream &os, const VersionInfo &obj)
{
  os << obj.to_string();

  return os;
}

// VersionInfo.cpp ends here.
