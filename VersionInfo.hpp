//
// VersionInfo.hpp --- Version information class.
//
// Copyright (c) 2013 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Wednesday May 29, 2013 20:52:03 asmodai>
// Revision:   24
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    29 May 2013 02:13:55
// Keywords:
// URL:        not distributed yet
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

#ifndef __VersionInfo_hpp__
#define __VersionInfo_hpp__

/**
 * @file VersionInfo.hpp
 * @author Paul Ward
 * @brief Version information class.
 */

#include <QtGlobal>
#include <QtCore/QDate>
#include <QtCore/QString>

/**
   @brief Version information class.
 
   This class contains the version number information of a project.
 
   It is designed to compose a version number out of four components:
 
     Component | Description
     ----------|------------
     major     | Major version number.
     minor     | Minor version number.
     patch     | Patch number.
     build     | A number generated from the build time.
 
   The output of the version number will look like
   @em 'major.minor.patch.build'.

   
   ###Creating version information###
   The constructor has three different overloads:
   @code{.cpp}
   VersionInfo vers = VersionInfo();
   @endcode
   The major, patch, and build number will default to 0.
   The minor number will default to 1.
   The start year of the project will default to the current year.
   
   @code{.cpp}
   VersionInfo vers = VersionInfo(4, 0, 1);
   @endcode
   The major, minor, and patch numbers are specified in the
   constructor.
   The build number will default to 0.
   The start year of the project will default to the current year.
   
   @code{.cpp}
   VersionInfo vers = VersionInfo(4, 0, 1, 1988);
   @endcode
   The major, minor, patch, and base year are specified in the
   constructor.
   The build number will default to 0.
   
   ###Specifying version information###
   As well as giving values during the construtor, the version
   information can be updated using methods:
   @code{.cpp}
   // 'vers' will essentially contain version 0.1.0.0
   VersionInfo vers = VersionInfo();
   
   // Set 'vers' to 10.5.8.0
   vers.setMajor(10);
   vers.setMinor(5);
   vers.setPatch(8);
   @endcode
   
   ###Incrementing version information###
   The version information can be incremented using simple methods
   such as:
   @code{.cpp}
   // 'vers' will contain 10.5.8.0
   VersionInfo vers = VersionInfo(10, 5, 8, 2000);
   
   // Increment to 11.6.9.0
   vers.incrementMajor();
   vers.incrementMinor();
   vers.incrementPatch();
   @endcode
   
   
   ###The build number###
   The method @c build() will return the build number of the project.
   The build number is defined using the current date, so it cannot be
   operated upon in the same way as the major, minor, and patch
   numbers.
   
   Simply calling @c build() will generate a new build number.  See
   the documentation for how it is generated.
   
   If you wish to re-generate a build number once an initial one has
   been returned, you will need to invalidate the cache with
   @c invalidateBuild().
   
   
   ###Example code###
   
   @code{.cpp}
   #include "VersionInfo.hpp"
   #include <QtCore/QString>
   #include <iostream>
   
   int
   main(int argc, char *argv)
   {
     VersionInfo ver = VersionInfo();
     
     ver.setMajor(10);
     ver.setMinor(5);
     ver.setPatch(8);
     ver.setBaseYear(1983);
     
     std::cout << "Version is:" << ver.toString().toStdString()
               << std::endl;
               
     return 0;
   }
   @endcode
   
   The output will be:
   @verbatim
   Version is: 10.5.8.36529
   @endverbatim
 */
class VersionInfo
{
private:
  int     m_major;              //!< Major version number.
  int     m_minor;              //!< Minor version number.
  int     m_patch;              //!< Patch number.
  int     m_build;              //!< Build number cache.
  int     m_baseYear;           //!< Year the project was started.
  QString m_string;             //!< String cache for string output.
  QDate   m_date;               //!< Date cache for build date output.
  
  
public:
  
  /**
   * @brief Constructor method.
   *
   * Generates a default version number of '0.1.0.x', where 'x' will
   * be the generated build number.
   */
  VersionInfo()
    : m_major(0),
      m_minor(1),
      m_patch(0),
      m_build(0)
  {
    m_baseYear = QDate::currentDate().year();
    m_string   = QString();
    m_date     = QDate();
  }
  
  /**
   * @brief Constructor method
   * @param major Major version number,
   * @param minor Minor version number.
   * @param patch Patch number.
   *
   * Generates a version number composed of @em 'major.minor.patch.x',
   * where @em 'x' will be the generated build number.
   */
  VersionInfo(const int major,
              const int minor,
              const int patch)
    : m_major(major),
      m_minor(minor),
      m_patch(patch),
      m_build(0)
  {
    m_baseYear = QDate::currentDate().year();
    m_string   = QString();
    m_date     = QDate();
    
    makeString();
    unmakeBuild();
  }
  
  /**
   * @brief Constructor method.
   * @param major Major verison number.
   * @param minor Minor version number.
   * @param patch Patch number,
   * @param baseYear Year project was started.
   *
   * Generates a version number composed of @em 'major.minor.patch.x',
   * where @em 'x' will be the generated build number.
   */
  VersionInfo(const int major,
              const int minor,
              const int patch,
              const int baseYear)
    : m_major(major),
      m_minor(minor),
      m_patch(patch),
      m_build(0)
  {
    m_baseYear = (baseYear > 0)
      ? baseYear
      : QDate::currentDate().year();
    m_string   = QString();
    m_date     = QDate();
    
    makeString();
    unmakeBuild();
  }
  
  /**
   * @brief Major version number component.
   * @returns The major version number.
   */
  int const &major(void) const
  {
    return m_major;
  }
  
  /**
   * @brief Set the major version number component.
   * @param value The major verison number.
   *
   * This method will invalidate the cached version string.
   */
  void setMajor(const int value)
  {
    m_major  = value;
    m_string = QString();
  }
  
  /**
   * @brief Increment the major version number.
   *
   * This method will invalidate the cached version string.
   */
  void incrementMajor(void)
  {
    m_major++;
    m_string = QString();
  }
  
  /**
   * @brief Minor version number component.
   * @returns The minor version number.
   */
  int const &minor(void) const
  {
    return m_minor;
  }
  
  /**
   * @brief Set the minor version number component.
   * @param value The minor version number.
   *
   * This method will invalidate the cached version string.
   */
  void setMinor(const int value)
  {
    m_minor  = value;
    m_string = QString();
  }
  
  /**
   * @brief Increment the minor version number.
   *
   * This method will invalidate the cached string.
   */
  void incrementMinor(void)
  {
    m_minor++;
    m_string = QString();
  }
  
  /**
   * @brief Patch number component.
   * @returns The patch number.
   */
  int const &patch(void) const
  {
    return m_patch;
  }
  
  /**
   * @brief Set the patch version component.
   * @param value The patch number.
   *
   * This method will invalidate the cached version string.
   */
  void setPatch(const int value)
  {
    m_patch  = value;
    m_string = QString();
  }
  
  /**
   * @brief Increment the patch number.
   *
   * This method will invalidate the cached string.
   */
  void incrementPatch(void)
  {
    m_patch++;
    m_string = QString();
  }
  
  /**
   * @brief Project base year.
   * @returns The year the project was started.
   */
  int const &baseYear(void) const
  {
    return m_baseYear;
  }
  
  /**
   * @brief Set the base year of the project.
   * @param value The base year.
   *
   * The @em base @em year is essentially the year in which the
   * project was started.  This is used to compute the build number.
   */
  void setBaseYear(const int value)
  {
    m_baseYear = value;
    m_string   = QString();
    m_date     = QDate();
  }
  
  /**
   * @brief Build number component.
   * @returns The build number.
   *
   * This method will only compute a build number if there is no
   * cached build number.  It will also invalidate both the cached
   * string and the cached date.
   */
  int build(void)
  {
    if (m_build == 0) {
      makeBuild();
    }
    
    m_string = QString();
    m_date   = QDate();
    
    return m_build;
  }
  
  /**
   * @brief Invalidate the build number.
   * @warning This must be used if you plan on generating a new buld
   *          number from a version that already has a build number.
   *          The algorithm is highly dependant on the current date,
   *          so once it is generated, it is cached.
   */
  void invalidateBuild(void)
  {
    m_build = 0;
  }
  
  /**
   * @brief Convert the version number to a string.
   * @returns A string containing the version number in the format of
   *          a.b.c.d
   *
   * This method will only compute a version string if there is no
   * cached string.
   */
  QString toString(void)
  {
    if (m_string.isNull()) {
      makeString();
    }
    
    return m_string;
  }
  
  /**
   * @brief Build date.
   * @returns The build date.
   *
   * This method will only compute a build date if there is no cached
   * date.
   */
  QDate buildDate(void)
  {
    if (m_date.isNull()) {
      m_date = unmakeBuild();
    }
    
    return m_date;
  }
  
  /**
   * @brief Equality test.
   * @param other A QDate to test against.
   * @returns @c true if the build date is the same as the given date;
   *          otherwise @c false is returned.
   *
   * If there is no cached date, this method will make one prior to
   * the equality check.  This means that this method will never be a
   * constant method.
   */
  bool operator == (const QDate &other)
  {
    if (m_date.isNull()) {
      m_date = unmakeBuild();
    }
    
    return m_date == other;
  }
  
  /**
   * @brief Inequality test.
   * @param other A QDate to test against.
   * @returns @c true if the build date is not the same as the given date;
   *          otherwise @c false is returned.
   *
   * If there is no cached date, this method will make one prior to
   * the equality check.  This means that this method will never be a
   * constant method.
   */
  bool operator != (const QDate &other)
  {
    if (m_date.isNull()) {
      m_date = unmakeBuild();
    }
    
    return m_date != other;
  }
  
  /**
   * @brief Equality test.
   * @param other A VersionInfo to test against.
   * @returns @c true if the version data is the same as the given version;
   *          otherwise @c false is returned.
   *
   * If there is no cached string, this method will make one prior to
   * the equality check.  This means that this method will never be a
   * constant method.
   */
  bool operator == (VersionInfo &other)
  {
    return (m_major == other.m_major)
      && (m_minor == other.m_minor)
      && (m_patch == other.m_patch)
      && (build() == other.build());
  }
  
  /**
   * @brief Inequality test.
   * @param other A VersionInfo to test against.
   * @returns @c true if the version data is not the same as the given
   *          version; otherwise @c false is returned.
   *
   * If there is no cached string, this method will make one prior to
   * the equality check.  This means that this method will never be a
   * constant method.
   */
  bool operator != (VersionInfo &other)
  {
    return (m_major != other.m_major)
      || (m_minor != other.m_minor)
      || (m_patch != other.m_patch)
      || (build() != other.build());
  }
  
  
private:
  
  /**
   * @brief Compute a build number.
   *
   * The build number is generated by the following:
   *
   *  * Take the year in which the project started.
   *  * Call January of that year 'month 1'.
   *  * The first two digits are the number of months since month 1.
   *  * The last two digits are the day of that month.
   */
  void makeBuild(void)
  {
    m_build = (((((QDate::currentDate().year() - m_baseYear) * 12)
                + QDate::currentDate().month()) * 100)
               + QDate::currentDate().day());
  }
  
  /**
   * @brief Convert the version information to a printable string.
   */
  void makeString(void)
  {
    QTextStream(&m_string) << m_major << "."
                           << m_minor << "."
                           << m_patch << "."
                           << build();
  }
  
  /**
   * @brief Return the date that a build number corresponds to.
   * @returns A QDate containing the year, month, and day of the build.
   *
   * Decomposes the build date from the build number.
   */
  QDate unmakeBuild(void)
  {
    QDate date = QDate();
    
    date.setDate(m_baseYear,
                 1,
                 (int)m_build % 100);
    date = date.addMonths((m_build / 100) - 1);
    
    return date;
  }
  
};                              // class VersionInfo

#endif // !__VersionInfo_hpp__

// VersionInfo.hpp ends here
