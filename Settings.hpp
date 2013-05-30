//
// Settings.hpp --- Version builder settings.
//
// Copyright (c) 2013 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Thursday May 30, 2013 11:45:52 asmodai>
// Revision:   13
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

#include <QtCore/QString>
#include <QtCore/QFile>

#include <tclap/CmdLine.h>
#include "version.hpp"

static QString
fromStdString(std::string &string)
{
  return QString::fromUtf8(string.data(), (int)string.size());
}

class Settings
{
private:
  QString m_filePath;
  QString m_format;
  bool    m_useStdOut;
  
public:
  
  typedef TCLAP::ValueArg<std::string> StringOpt;
  
  Settings(int argc, char **argv)
  {
    try {
      TCLAP::CmdLine cmd("", ' ', VERSION_STRING, true);
      
      StringOpt fileName("o",
                         "output",
                         "File containing version information.",
                         false,
                         "",
                         "string");
      StringOpt verFmt("f",
                       "format",
                       "Version number format string.",
                       false,
                       "*.*.+.*",
                       "string");
      
      cmd.add(fileName);
      cmd.add(verFmt);
      cmd.parse(argc, argv);
      
      m_filePath = fromStdString(fileName.getValue()); 
      m_format   = fromStdString(verFmt.getValue());
      
      if (m_filePath.isNull() || m_filePath.length() == 0)
      {  
        m_useStdOut = true;
      } else {
        m_useStdOut = false;
      }
    }
    
    catch (TCLAP::ArgException &e) {
      std::cerr << "Error: " << e.error()
                << " for arg " << e.argId()
                << std::endl;
    }
  }
  
  const QString &filePath(void) const
  {
    return m_filePath;
  }
  
  const QString &versionFormat(void) const
  {
    return m_format;
  }
  
  const bool &useStdOut(void) const
  {
    return m_useStdOut;
  }
  
};


#endif // !__Settings_h__

// Settings.hpp ends here

