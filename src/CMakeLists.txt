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
target_link_libraries(
  verbuild PRIVATE
    ${Boost_LIBRARIES}
)

# Set up include paths.
message(STATUS "Boost includes at '${Boost_INCLUDE_DIRS}'")
target_include_directories(
  verbuild PUBLIC
    ${Boost_INCLUDE_DIRS}
)
target_include_directories(
  COMMON_OBJECTS PUBLIC
    ${Boost_INCLUDE_DIRS}
)

# Generate tests.
foreach(testSrc ${TEST_SRCS})
  get_filename_component(testName ${testSrc} NAME_WE)
  add_executable(${testName} ${testSrc} $<TARGET_OBJECTS:COMMON_OBJECTS>)
  target_link_libraries(${testName} ${Boost_LIBRARIES})
  target_include_directories(${testName} PRIVATE ${Boost_INCLUDE_DIRS})
  add_test(NAME ${testName} COMMAND ${testName} -r detailed)
endforeach(testSrc)

# EOF
