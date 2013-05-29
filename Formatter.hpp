//
// Output.hpp --- Output meta class.
//
// Copyright (c) 2013 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Wednesday May 29, 2013 21:07:37 asmodai>
// Revision:   27
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

#ifndef _Output_h_
#define _Output_h_

/**
 * @file Output.hpp
 * @author Paul Ward
 * @brief Output meta class.
 */

#include <QtGlobal>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include "VersionInfo.hpp"
#include "version.hpp"

#include <cassert>
#include <vector>
#include <utility>


/**
   @def OUTPUT_PREAMBLE
   @brief Convenience macro for generating output subclass constructor
          methods.
   @param TYPE The type of the output formatter module.
   @param NAME The human-readable pretty name of the output formatter
          module.
   @see OUTPUT_REGISTER
   
   This macro is designed to save having to type the same three
   constructor methods each time a new output class is added.
   
   Example:
   @code{.cpp}
   class FooOutput
     : Output
   {
   public:
     OUTPUT_PREAMBLE(FooOutput, "Foo Output Formatter")
     
     // ...
   }
   @endcode
 */
#define OUTPUT_PREAMBLE(TYPE, NAME)                  \
  private:                                           \
  static const std::size_t s_id;                     \
  static Output *create() { return new TYPE; }       \
  public:                                            \
  TYPE()                                             \
    : Output()                                       \
  { m_outputName = NAME; }                           \
  TYPE(const QString &file)                          \
    : Output(file)                                   \
  { m_outputName = NAME; }                           \
  TYPE(const QString &file, const OutputFlags flags) \
    : Output(file, flags)                            \
  { m_outputName = NAME; }


/**
 * @brief Output meta class.
 *
 * This class is an abstraction that provides file writing
 * functionality.  What this means is that Output subclasses are
 * responsible for writing version information out to file.
 */
class Output
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
  QString     m_outputName;     //!< Output pretty name.
  QString     m_fileName;       //!< Version information file name.
  OutputFlags m_flags;          //!< Output flags.
  
public:
  
  /**
   * @brief Default constructor method.
   *
   * Initialises the file name to a Null string and sets the output
   * flags to Output::All.
   */
  Output()
  {
    m_fileName = QString();
    m_flags    = Output::All;
  }
  
  /**
   * @brief Constructor method.
   * @param file The name of the file to write information to.
   *
   * Initialises the output flags to Output::All.
   */
  Output(const QString &file)
    : m_fileName(file)
  {
    m_flags = Output::All;
  }
  
  /**
   * @brief Constructor method.
   * @param file The name of the file to write information to.
   * @param flags The output flags.
   */
  Output(const QString &file, const OutputFlags flags)
    : m_fileName(file),
      m_flags(flags)
  {}
  
  /**
   * @brief Return the human-readable name for this output formatter.
   * @returns The human-readable name as a QString constant.
   */
  virtual QString const &outputName(void) const
  {
    return m_outputName;
  }
  
  /**
   * @brief Set the output file name to the file specified in
   *        @em name.
   * @param name The name of the output file name.
   */
  virtual void setFileName(const QString &name)
  {
    m_fileName = name;
  }
  
  /**
   * @brief Return the output file name.
   * @returns The output file name in the form of a QString.
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
   * @brief Write the version information to a file.
   * @param info The version information to write to file.
   * @returns @c true if the write was successful; otherwise @c false
   *          is returned.
   */
  virtual bool write(VersionInfo info) = 0;
  
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
                     VersionInfo        info) = 0;
  
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
 * @brief Output creation function.
 */
typedef Output *(*OutputCreateFn)(void);

/**
 * @brief Map of output names and creation functions.
 */
typedef std::map<std::string, OutputCreateFn> OutputMap;

/**
 * @brief Output formatter class factory.
 */
class OutputFactory
{
private:
  static OutputMap   s_map;     //!< Map of names and creation functions.
  static std::size_t s_id;      //!< ID of output class within list. (internal)
  
  
public:
  /**
   * @brief Register an output class creation function.
   * @param creator The object creation method.
   * @param name The name of the output formatting module.
   * @returns The size of the name/class map after the new output
   *          class has been registered.
   * @note The return value is largely meaningless.
   * @note The output formatting module name is @em not the same as
   *       the human-readable name.
   */
  static std::size_t registerOutput(OutputCreateFn creator, std::string name)
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
  static Output *create(std::string name)
  {
    assert(name.length() > 0);
    
    return (s_map[name])();
  }
  
};

/* Initial value. */
OutputMap OutputFactory::s_map = OutputMap();

/**
   @def OUTPUT_REGISTER
   @brief Register an output formatter module.
   @param TYPE The type of the output formatter module.
   @param NAME The name of the output formatter module.
   @note The name given here is not the same as the human-readable
         name used by @c OUTPUT_PREAMBLE, so please be aware of this.
   @see OUTPUT_PREAMBLE
   
   Registers a new formatter module at compile-time.
   
   Example:
   @code{.cpp}
   class FooOutput
     : Output
   {
     // ...
   }
   OUTPUT_REGISTER(FooOutput, "Foo")
   @endcode
 */
   
#define OUTPUT_REGISTER(TYPE, NAME)             \
  const std::size_t TYPE::s_id = OutputFactory::registerOutput(&create, NAME);

#endif // !_Output_h_

// Output.hpp ends here
