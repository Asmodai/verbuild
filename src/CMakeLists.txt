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
  set(WITH_LIBS "${WITH_LIBS};${Boost_SYSTEM_LIBRARY}")
  set(WITH_LIBS "${WITH_LIBS};${PTHREAD_LIBRARY}")
else()
  set(WITH_LIBS "${Boost_LIBRARIES}")
endif()

# Add Lua
add_subdirectory(lua)
include_directories(${LUA_INCLUDE})
add_subdirectory(sol2)

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
  ${LUA_SRCS}
)

# Set libraries to link with.
target_link_libraries(verbuild PUBLIC
  ${WITH_LIBS}
  ${CMAKE_THREAD_LIBS_INIT}
  sol2::sol2
)

# Set up properties.
set_target_properties(
  verbuild
  PROPERTIES CXX_STANDARD          17
             CXX_STANDARD_REQUIRED ON
             CXX_EXTENSIONS        OFF
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

# Something about dog food.
if(WIN32)
  set(DOG_FOOD_SCRIPT "${PROJECT_SOURCE_DIR}/scripts/dog-food.bat")
  set(DOG_FOOD_BINARY "${CMAKE_CURRENT_BINARY_DIR}/verbuild.exe")
else()
  set(DOG_FOOD_SCRIPT "${PROJECT_SOURCE_DIR}/scripts/dog-food")
  set(DOG_FOOD_BINARY "${CMAKE_CURRENT_BINARY_DIR}/verbuild")
endif()

add_custom_target(
  verbuild_version
  COMMAND ${DOG_FOOD_SCRIPT}
          ${DOG_FOOD_BINARY}
          ${CMAKE_CURRENT_SOURCE_DIR}/verbuild/version.hpp)
add_dependencies(verbuild verbuild_version)

# Set up installation
install(TARGETS verbuild DESTINATION bin)

# EOF
