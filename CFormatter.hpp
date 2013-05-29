//
// COutput.hpp --- C/C++ header output.
//
// Copyright (c) 2013 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Wednesday May 29, 2013 20:04:52 asmodai>
// Revision:   15
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    29 May 2013 04:19:38
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

#ifndef _COutput_hpp_
#define _COutput_hpp_

/**
 * @file COutput.hpp
 * @author Paul Ward
 * @brief Outputs version information to C/C++ header files.
 */

#include "Output.hpp"

class COutput
  : public Output
{
  OUTPUT_PREAMBLE(COutput, "C/C++")

  
public:
  
  bool write(VersionInfo info)
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
  
  bool write(QTextStream       &stream,
             const OutputFlags  flags,
             VersionInfo        info)
  {
    m_flags = flags;
    
    return write(stream, info);
  }
  
  bool write(QTextStream &stream,
             VersionInfo  info)
  {
    stream << "/* --------------------------------------------"         << endl
           << " * Automatically generated by VerBuild "
           << VERSION_STRING << "."                                     << endl
           << " * Do not edit by hand."                                 << endl
           << " * --------------------------------------------"         << endl
           << " */"                                                     << endl
           << endl
           << "#ifndef __VersionInfo_Header__"                          << endl
           << "#define __VersionInfo_Header__"                          << endl
           << endl;
    
    if (m_flags & Output::Doxygen) {
      stream << "/**"                                                   << endl
             << " * @file " << m_fileName                               << endl
             << " * @author VarBuild " << VERSION_STRING                << endl
             << " * @brief Provides version information."               << endl
             << " */"                                                   << endl
             << endl;
    }
    
    if (m_flags & Output::Basic) {
      if (m_flags & Output::Doxygen) {
        stream << "/**"                                                 << endl
               << " * @def VERSION_MAJOR"                               << endl
               << " * @brief Major version number."                     << endl
               << " *"                                                  << endl
               << " * @def VERSION_MINOR"                               << endl
               << " * @brief Minor version number."                     << endl
               << " *"                                                  << endl
               << " * @def VERSION_PATCH"                               << endl
               << " * @brief Patch number."                             << endl
               << " *"                                                  << endl
               << " * @def VERSION_BUILD"                               << endl
               << " * @brief Build number."                             << endl
               << " *"                                                  << endl
               << " * @def VERSION_BASE_YEAR"                           << endl
               << " * @brief The year the project was started."         << endl
               << " *"                                                  << endl
               << " * @def VERSION_DATE"                                << endl
               << " * @brief The date this build was compiled."         << endl
               << " *"                                                  << endl
               << " * @def VERSION_TIME"                                << endl
               << " * @brief The time this build was compiled."         << endl
               << " *"                                                  << endl
               << " * @def VERSION_STRING"                              << endl
               << " * @brief String representation of the version."     << endl
               << " */"
               << endl;
      }
      
      stream << "#define VERSION_MAJOR      " << info.major()           << endl
             << "#define VERSION_MINOR      " << info.minor()           << endl
             << "#define VERSION_PATCH      " << info.patch()           << endl
             << "#define VERSION_BUILD      " << info.build()           << endl
             << endl
             << "#define VERSION_BASE_YEAR  " << info.baseYear()        << endl
             << "#define VERSION_DATE       "
                << "\"" << info.buildDate().toString() << "\""          << endl
             << "#define VERSION_TIME       "
                << "\"" << QTime::currentTime().toString() << "\""      << endl
             << "#define VERSION_STRING     "
                << "\"" << info.toString() << "\""                      << endl
             << endl;
    }
    
    if (m_flags & Output::Struct) {
      if (m_flags & Output::Doxygen) {
        stream << "/**"                                                 << endl
               << " * @brief Version number structure."                 << endl
               << " *"                                                  << endl
               << " * @var major"                                       << endl
               << " * @brief Major version number"                      << endl
               << " *"                                                  << endl
               << " * @var minor"                                       << endl
               << " * @brief Minor version number."                     << endl
               << " *"                                                  << endl
               << " * @var patch"                                       << endl
               << " * @brief Patch number."                             << endl
               << " *"                                                  << endl
               << " * @var build"                                       << endl
               << " * @brief Build number."                             << endl
               << " */"
               << endl;
      }
          
      stream << "static struct VersionNumber_s {"                       << endl
             << "  int major;"                                          << endl
             << "  int minor;"                                          << endl
             << "  int patch;"                                          << endl
             << "  int build;"                                          << endl
             << "} VersionNumber = {"                                   << endl
             << "  " << info.major() << ","                             << endl
             << "  " << info.minor() << ","                             << endl
             << "  " << info.patch() << ","                             << endl
             << "  " << info.build() << ","                             << endl
             << "};"                                                    << endl
             << endl;
    }
      
    stream << "#endif // !__VersionInfo_Header__"
           << endl;
    
    return true;
  }                             // write(QTextStream &...)
  
};                              // class COutput

OUTPUT_REGISTER(COutput, "C")

#endif // !_COutput_hpp_

// COutput.hpp ends here