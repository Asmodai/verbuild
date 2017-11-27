#
# CMakeLists.txt --- CMake project configuration.
#
# Copyright (c) 2013-2017 Paul Ward <asmodai@gmail.com>
#
# Author:     Paul Ward <asmodai@gmail.com>
# Maintainer: Paul Ward <asmodai@gmail.com>
# Created:    19 Nov 2017 02:15:34
#
# {{{ License:
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 3
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, see <http://www.gnu.org/licenses/>.
#
# }}}
# {{{ Commentary:
#
# }}}

# Set up includes and libraries
set(WITH_INCS "${Boost_INCLUDE_DIRS}")

if(STATIC)
  set(WITH_LIBS "${WITH_LIBS};${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}")
  set(WITH_LIBS "${WITH_LIBS};${Boost_REGEX_LIBRARY}")
  set(WITH_LIBS "${WITH_LIBS};${Boost_DATE_TIME_LIBRARY}")
  set(WITH_LIBS "${WITH_LIBS};${Boost_PROGRAM_OPTIONS_LIBRARY}")
  set(WITH_LIBS "${WITH_LIBS};${Boost_LOCALE_LIBRARY}")
  set(WITH_LIBS "${WITH_LIBS};${Boost_FILESYSTEM_LIBRARY}")
  set(WITH_LIBS "${WITH_LIBS};${PTHREAD_LIBRARY};${Boost_SYSTEM_LIBRARY}")
  message(STATUS "Static libraries: ${WITH_LIBS}")
else()
  set(WITH_LIBS "${Boost_LIBRARIES}")
endif()

#if(FLTK_FOUND)
#  set(WITH_INCS "${WITH_INCS};${FLTK_INCLUDE_DIR}")
#  set(WITH_LIBS "${WITH_LIBS};${FLTK_BASE_LIBRARY}")
#endif()

# GUI components
#if(FLTK_FOUND)
#  file(GLOB UI_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} gui/*.cpp)
#else()
#  set(UI_OBJECTS "")
#endif()
#add_library(UI_OBJECTS OBJECT ${UI_SOURCES})
#target_include_directories(UI_OBJECTS PUBLIC ${WITH_INCS})
#
# Code shared between app and tests.
file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} verbuild/*.cpp)
list(REMOVE_ITEM SOURCES "verbuild/main.cpp")

# Test sources.
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} tests/*.cpp)

# Object 'library' of shared code.
add_library(COMMON_OBJECTS OBJECT ${SOURCES})

# Main binary.
add_executable(
  verbuild 
    "verbuild/main.cpp"
    "verbuild/resource.rc"
  $<TARGET_OBJECTS:COMMON_OBJECTS>
)

# Set libraries to link with.
target_link_libraries(verbuild PUBLIC
  ${WITH_LIBS}
  ${CMAKE_THREAD_LIBS_INIT}
)

# Set up include paths.
target_include_directories(verbuild PUBLIC ${WITH_INCS})
target_include_directories(COMMON_OBJECTS PUBLIC ${WITH_INCS})

# Generate tests.
foreach(testSrc ${TEST_SRCS})
  get_filename_component(testName ${testSrc} NAME_WE)
  add_executable(${testName} ${testSrc} $<TARGET_OBJECTS:COMMON_OBJECTS>)
  target_link_libraries(${testName} ${WITH_LIBS})
  target_include_directories(${testName} PUBLIC ${WITH_INCS})
  add_test(NAME ${testName} COMMAND ${testName} -r detailed)
endforeach(testSrc)

# Set up installation
install(TARGETS verbuild DESTINATION bin)

# EOF
