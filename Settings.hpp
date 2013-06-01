//
// Settings.hpp --- Version builder settings.
//
// Copyright (c) 2013 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Saturday Jun  1, 2013 04:40:19 asmodai>
// Revision:   20
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    30 May 2013 01:16:19
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
// along with this program; if not, see  <http://www.gnu.org/licenses/>.
//
// }}}
// {{{ Commentary:

// }}}

#ifndef __Settings_hpp__
#define __Settings_hpp__

/**
 * @file Settings.hpp
 * @author Paul Ward
 * @brief Command line parsing and program settings.
 */

#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QDate>
#include <QtCore/QRegExp>
#include <QtCore/QFlags>

#include <tclap/CmdLine.h>

#include "Enums.hpp"
#include "version.hpp"


/**
   @def FRE
   @brief Regular expression to match a version number format
          specifier.
   @see FormatConstraint

   This regular expression will match a string with the format of
   'x.x.x.x'.
   
 */
   
#define FRE                                     \
  "([\\*\\+\\d]+\\.){3,3}([\\*\\+\\d]+){1,1}"


/**
   @brief Version number format constraint.
   
   The format required for a version number is 'x.x.x.x', where @em x
   can be one of the following:
   
   Format     | Description
   :---------:|--------------------------------
   @b \*      | Number component is left as-is.
   @b \+      | Number component is incremented.
   @b [0-9]\+ | Number component is a constant.
   
   As an example, if we have a format string of '10.*.+.*', then the
   version number will contain the following components:
   
   Component | Description
   :--------:|---------------------------
   @b 10     | The major version will always have the value 10.
   @b \*     | The minor number will be left as-is.
   @b \+     | The patch number will be incremented.
   @b \*     | The build number will be left as-is. 
   
   Therefore, if the version number is read in from a header as
   @em 5.5.8.1, then after processing, the format will result in a
   new version number of @em 10.5.9.1.
 */
class FormatConstraint
  : public TCLAP::Constraint<std::string>
{
protected:
  std::string _typeDesc;        //!< Constraint description.
  
  
public:

  /**
   * @brief Constructor method.
   * @note The argument is not used.
   */
  FormatConstraint(std::vector<std::string> &)
  {
    _typeDesc = "x.x.x.x";
  }

  /**
   * @brief Constraint description.
   * @returns An @c std::string describing the constraint.
   */
  virtual std::string description(void) const
  {
    return _typeDesc;
  }
  
  /**
   * @brief Constraint short identifier.
   * @returns An @c std::string containing an identifier.
   *
   * This identifier is the one that is showen when TCLAP generates a
   * usage message.
   */
  virtual std::string shortID(void) const
  {
    return _typeDesc;
  }
  
  /**
   * @brief Check the validity of the given value.
   * @returns @c true if the value is valid; otherwise @c false is
   *          returned.
   * @see FRE
   *
   * Attempts to match the given format string value with a regular
   * expression.  If there is an exact match, then the value is
   * considered valid.
   */
  virtual bool check(const std::string &value) const;
  
};                              // class FormatConstraint


/**
 * @brief Year constraint.
 *
 * When a year is requested via a command-line argument, it must be a
 * valid year, within reason.
 *
 * What dictates reason?  Is a project start date of 55 C.E. valid?
 * What about a start date of 2149?
 *
 * This constraint will limit years to a range of
 * [1970...@c <current @c year>
 */
class YearConstraint
  : public TCLAP::Constraint<int>
{
protected:
  std::string _typeDesc;        //!< Constraint description.
  
  
public:
    
  /**
   * @brief Constructor method.
   * @note The argument is not used.
   */
  YearConstraint(std::vector<int> &)
  {
    QString tmp;
    
    tmp.sprintf("[1970...%d]", QDate::currentDate().year());
    
    _typeDesc = tmp.toStdString();
  }
  
  /**
   * @brief Constraint description.
   * @returns An @c std::string describing the constraint.
   */
  virtual std::string description(void) const
  {
    return _typeDesc;
  }
  
  /**
   * @brief Constraint short identifier.
   * @returns An @c std::string containing an identifier.
   *
   * This identifier is the one that is showen when TCLAP generates a
   * usage message.
   */
  virtual std::string shortID(void) const
  {
    return _typeDesc;
  }
  
  /**
   * @brief Check the validity of the given value.
   * @returns @c true if the value is valid; otherwise @c false is
   *          returned.
   *
   * Checks whether the value is in the range
   * [1970...@c <current @c year>.
   */
  virtual bool check(const int &value) const
  {
    return (value >= 1970 && value <= QDate::currentDate().year());
  }
  
};                              // class YearConstraint


/**
 * @brief Command-line parser and program settings.
 */
class Settings
{  
private:
  QString    m_filePath;        //!< Path to the file to output info to.
  QString    m_format;          //!< Version number format string.
  bool       m_useStdOut;       //!< Write output to stdout?
  bool       m_overflow;        //!< Overflow shifting enabled?
  int        m_baseYear;        //!< The base year of the project.
  BuildTypes m_incrType;        //!< Increment type.
  
  
public:
  
  /**
   * @brief String command-line argument.
   */
  typedef TCLAP::ValueArg<std::string> StringOpt;
  
  /**
   * @brief Integer command-line argument.
   */
  typedef TCLAP::ValueArg<int> IntOpt;
  
  /**
   * @brief Constructor method.
   * @param argc Count of arguments.
   * @param argv Array of arguments.
   */
  Settings(int argc, char **argv);
  
  /**
   * @brief Return the file name and path to which we will write
   *        version information.
   * @returns A string containing the file name and path.
   */
  const QString &filePath(void) const
  {
    return m_filePath;
  }
  
  /**
   * @brief Return the version number format string.
   * @returns A string containing the format string.
   */
  const QString &versionFormat(void) const
  {
    return m_format;
  }
  
  /**
   * @brief Do we write version information to standard output?
   * @returns @c true if we do; otherwise @c false is returned.
   */
  const bool &useStdOut(void) const
  {
    return m_useStdOut;
  }
  
  /**
   * @brief Return the base year of the project.
   * @returns An integer containing the base year.
   */
  const int &baseYear(void) const
  {
    return m_baseYear;
  }

  /**
   * @brief Return the incrementation type.
   * @returns The incrementation type/
   */
  const BuildTypes incrementType(void) const
  {
    return m_incrType;
  }
  
  /**
   * @brief Do we do any integer overflow testing and shift
   *        accordingly?
   * @returns @c true if overflow detection and shifting is desired;
   *          otherwise return @c false.
   */
  const bool &overflowShift(void) const
  {
    return m_overflow;
  }

  /**
   * @brief Dump the settings to standard output.
   */
  void dump(void) const;
  
};                              // class Settings

#endif // !__Settings_h__

// Settings.hpp ends here
