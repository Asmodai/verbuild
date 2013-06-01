//
// Formatter.hpp --- Output meta class.
//
// Copyright (c) 2013 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Saturday Jun  1, 2013 05:04:36 asmodai>
// Revision:   42
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    29 May 2013 04:13:11
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

#ifndef __Formatter_hpp__
#define __Formatter_hpp__

/**
 * @file Formatter.hpp
 * @author Paul Ward
 * @brief Source formatter meta class.
 */

#include <QtGlobal>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QRegExp>

#include "VersionInfo.hpp"
#include "version.hpp"

#include <cassert>
#include <vector>
#include <utility>


/**
   @def FORMATTER_PREAMBLE
   @brief Convenience macro for generating output subclass constructor
          methods.
   @param TYPE The type of the formatter module.
   @param NAME The human-readable pretty name of the formatter module.
   @see FORMATTER_REGISTER
   
   This macro is designed to save having to type the same three
   constructor methods each time a new output class is added.
   
   Example:
   @code{.cpp}
   class FooFormatter
     : Formatter
   {
   public:
     FORMATTER_PREAMBLE(FooFormatter, "Foo Formatter")
     
     // ...
   }
   @endcode
 */
#define FORMATTER_PREAMBLE(TYPE, NAME)                  \
  private:                                              \
    static const std::size_t s_id;                      \
    static Formatter *create(void) { return new TYPE; } \
  public:                                               \
    TYPE()                                              \
      : Formatter()                                     \
    { m_formatterName = NAME; }                         \
    TYPE(const QString &file)                           \
      : Formatter(file)                                 \
    { m_formatterName = NAME; }                         \
    TYPE(const QString &file, const OutputFlags flags)  \
      : Formatter(file, flags)                          \
    { m_formatterName = NAME; }


/**
 * @brief Formatter meta class.
 *
 * This class is an abstraction that provides file writing
 * functionality.  What this means is that Formatter subclasses are
 * responsible for reading and writing version information to and
 * from files.
 */
class Formatter
{  
public:
  
  /**
   * @enum OutputFlag
   * @brief Output flags
   * 
   * Controls how version information is written out to file.
   *
   * @b Basic writes out the version information in the most basic
   * form possible -- i.e. for C or C++, the information is written
   * out as a series of preprocessor statements.
   *
   * @b Struct writes out the version information in the form of some
   * form of structure -- i.e. for C or C++, the information is
   * written out as a @c struct statement.
   *
   * @b Doxygen causes documentation that Doxygen can use to be
   * written out to the file.
   *
   * @b All does what you think it would do.
   *
   * @var Basic
   * @brief Basic version information.
   *
   * @var Struct
   * @brief A structure is created containing version information.
   *
   * @var Doxygen
   * @brief Doxygen documentation is included.
   *
   * @var All
   * @brief Everything possible is included.
   */
  enum OutputFlag {
    Basic   = 0x01,
    Struct  = 0x02,
    Doxygen = 0x04,
    All     = Basic | Struct | Doxygen
  };
  Q_DECLARE_FLAGS(OutputFlags, OutputFlag)
  
  
protected:
  QString     m_formatterName;  //!< Formatter pretty name.
  QString     m_fileName;       //!< Version information file name.
  OutputFlags m_flags;          //!< Output flags.
  
  
public:
  
  /**
   * @brief Default constructor method.
   *
   * Initialises the file name to a Null string and sets the output
   * flags to Output::All.
   */
  Formatter()
  {
    m_formatterName = QString("<unknown>");
    m_fileName      = QString();
    m_flags         = Formatter::All;
  }
  
  /**
   * @brief Constructor method.
   * @param file The name of the file to read and write.
   *
   * Initialises the output flags to Formatter::All.
   */
  Formatter(const QString &file)
    : m_fileName(file)
  {
    m_formatterName = QString("<unknown>");
    m_flags         = Formatter::All;
  }
  
  /**
   * @brief Constructor method.
   * @param file The name of the file to read and write.
   * @param flags The output flags.
   */
  Formatter(const QString &file, const OutputFlags flags)
    : m_fileName(file),
      m_flags(flags)
  {
    m_formatterName = QString("<unknown>");
  }
  
  /**
   * @brief Destructor method.
   */
  virtual ~Formatter()
  {}
  
  /**
   * @brief Return the human-readable name for this formatter.
   * @returns The human-readable name as a QString constant.
   */
  virtual QString const &formatterName(void) const
  {
    return m_formatterName;
  }
  
  /**
   * @brief Set the formatter file name to the file specified in
   *        @em name.
   * @param name The name of the file.
   */
  virtual void setFileName(const QString &name)
  {
    m_fileName = name;
  }
  
  /**
   * @brief Return the formatter file name.
   * @returns The file name in the form of a QString.
   */
  virtual QString const &fileName(void) const
  {
    return m_fileName;
  }
  
  /**
   * @brief Set the output flags to the flags specified in
   *        @em flags.
   * @param flags The output flags.
   */
  virtual void setFlags(const OutputFlags flags)
  {
    m_flags = flags;
  }
  
  /**
   * @brief Return the output flags.
   * @returns The output flags.
   */
  virtual OutputFlags const &flags(void) const
  {
    return m_flags;
  }
  
  /**
   * @brief Read the version information from a file.
   * @param info Pointer to the version information object to store
   *             the data in.
   * @returns @c true if the read was successful; otherwise @c false
   *          is returned.
   */
  virtual bool read(VersionInfo &info)
  {
    if (!m_fileName.isNull()) {
      QFile file(m_fileName);
      
      file.open(QIODevice::ReadOnly | QIODevice::Text);
      if (file.isOpen()) {
        QTextStream stream(&file);
        
        read(stream, info);
        file.close();
        
        return true;
      }
    }
    
    return false;
  }
  
  /**
   * @brief Read the version information from a file.
   * @param stream The text stream to read the information from.
   * @param info Pointer to the version information object to store
   *             the data in.
   * @returns @c true if the read was successful; otherwise @c false
   *          is returned.
   */
  virtual bool read(QTextStream &stream, VersionInfo &info) = 0;
  
  /**
   * @brief Write the version information to a file.
   * @param info The version information to write to file.
   * @returns @c true if the write was successful; otherwise @c false
   *          is returned.
   */
  virtual bool write(VersionInfo info)
  {
    if (!m_fileName.isNull()) {
      QFile file(m_fileName);
      
      file.open(QIODevice::WriteOnly | QIODevice::Text);
      if (file.isOpen()) {
        QTextStream stream(&file);
        
        write(stream, info);
        file.close();
        
        return true;
      }
    }
    
    return false;
  }
  
  /**
   * @brief Write the version information to a file.
   * @param stream The text stream to output the information to.
   * @param flags The output flags.
   * @param info The version information to write to file.
   * @returns @c true if the write was successful; otherwise @c false
   *          is returned.
   * @overload
   */
  virtual bool write(QTextStream       &stream,
                     const OutputFlags  flags,
                     VersionInfo        info)
  {
    m_flags = flags;
    
    return write(stream, info);
  }
  
  /**
   * @brief Write the version information to a file.
   * @param stream The text stream to output the information to.
   * @param info The version information to write to file.
   * @returns @c true if the write was successful; otherwise @c false
   *          is returned.
   * @overload
   */
  virtual bool write(QTextStream &stream,
                     VersionInfo  info) = 0;
  
};                              // class Output

/**
 * @brief Formatter creation function.
 */
typedef Formatter *(*FormatterCreateFn)(void);

/**
 * @brief Map of formatter names and creation functions.
 */
typedef std::map<std::string, FormatterCreateFn> FormatterMap;

/**
 * @brief Formatter class factory.
 */
class FormatterFactory
{
private:
  static FormatterMap s_map;    //!< Map of names and creation functions.
  static std::size_t  s_id;     //!< ID of output class within list. (internal)
  
  
public:
  /**
   * @brief Register a formatter class creation function.
   * @param creator The object creation method.
   * @param name The name of the formatting module.
   * @returns The size of the name/class map after the new output
   *          class has been registered.
   * @note The return value is largely meaningless.
   * @note The output formatting module name is @em not the same as
   *       the human-readable name.
   */
  static std::size_t registerFormatter(FormatterCreateFn creator,
                                       std::string       name)
  {
    assert(creator);
    assert(name.length() > 0);
    
    s_map[name] = creator;
    
    return s_map.size();
  }
  
  /**
   * @brief Create a new instance of the output formatter specified
   *        with @em name.
   * @param name The output formatter name.
   * @returns A new instance of a formatter module.
   * @note The output formatting module name is @em not the same as
   *       the human-readable name.
   */
  static Formatter *create(std::string name)
  {
    assert(name.length() > 0);
    
    return (s_map[name])();
  }
  
};                              // class FormatterFactory

/* Initial value. */
FormatterMap FormatterFactory::s_map = FormatterMap();

/**
   @def FORMATTER_REGISTER
   @brief Register an output formatter module.
   @param TYPE The type of the formatter module.
   @param NAME The name of the formatter module.
   @note The name given here is not the same as the human-readable
         name used by @c FORMATTER_PREAMBLE, so please be aware of this.
   @see FORMATTER_PREAMBLE
   
   Registers a new formatter module at compile-time.
   
   Example:
   @code{.cpp}
   class FooFormatter
     : Formatter
   {
     // ...
   }
   FORMATTER_REGISTER(FooFormatter, "Foo")
   @endcode
 */
#define FORMATTER_REGISTER(TYPE, NAME)                  \
  const std::size_t TYPE::s_id =                        \
    FormatterFactory::registerFormatter(&create, NAME);

#endif // !__Formatter_hpp__

// Formatter.hpp ends here
