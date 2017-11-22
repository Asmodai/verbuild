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

cmake_minimum_required(VERSION 2.6)

project(verbuild)

# Before anything, ensure we can C++11!
if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")
endif()

# Catch debug
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

set(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH})

enable_testing()
include(GetGitRevisionDescription)

# Git version info
git_describe(GIT_DESCRIBE "--always")
add_definitions(-D_GIT_VERSION="${GIT_DESCRIBE}")

# Git SHA1 define
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
add_definitions(-D_GIT_SHA1="${GIT_SHA1}")

# Boost
#add_definitions(-DBOOST_ALL_DYN_LINK)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.65.0 REQUIRED
  program_options
  date_time
  unit_test_framework)

# Add Boost includes
if (Boost_FOUND)
  message(STATUS "Boost inc  = '${Boost_INCLUDE_DIRS}'")
  message(STATUS "Boost libs = '${Boost_LIBRARIES}'")
  include_directories(${Boost_INCLUDE_DIRS})
endif()

# Unit tests
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/tests/*.cpp)
file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/verbuild/*.cpp)
list(REMOVE_ITEM SOURCES "src/verbuild/main.cpp")
foreach(testSrc ${TEST_SRCS})
  get_filename_component(testName ${testSrc} NAME_WE)
  add_executable(${testName} ${testSrc} ${SOURCES})
  target_link_libraries(${testName} ${Boost_LIBRARIES})
  set_target_properties(${testName} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin)
  add_test(NAME ${testName} 
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin 
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName} -r detailed)
endforeach(testSrc)

add_subdirectory("src")
