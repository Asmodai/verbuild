Hi, Emacs: -*- mode: gfm -*-

# verbuild

Version number auto-incrementing and build numbering tool.

## Table of Contents

   * [verbuild](#verbuild)
      * [How to build](#how-to-build)
         * [CMake options](#cmake-options)
      * [How it works](#how-it-works)
         * [Simple incrementation](#simple-incrementation)
         * [Month offset incrementation](#month-offset-incrementation)
         * [Year offset incrementation](#year-offset-incrementation)
         * [Date incrementation](#date-incrementation)
      * [Output](#output)
      * [Input](#input)
      * [Flags and options](#flags-and-options)
         * [General options](#general-options)
         * [Increment options](#increment-options)
         * [Transform options](#transform-options)
         * [Output options](#output-options)
         * [Information options](#information-options)
         * [Debug options](#debug-options)
      * [Examples](#examples)

## How to build

Verbuild uses [CMake](https://cmake.org) as its build system, and requires
[Boost](https://www.boost.org) 1.65 or higher to be installed.

To build verbuild with CMake, issue the following instructions:

### Unix and Unix-like

``` shell
mkdir build
cd build
cmake ..
make
sudo make install
```

### Windows

Unfortunately, there is no easy way to install on Windows right now.
You will probably need to use Explorer or PowerShell to copy the
executable to a place on your path.

### CMake options

For a more complete list of what CMake can do, please refer to the CMake
manual.  Here are some common recipes, however:

#### -DCMAKE_BUILD_TYPE=Release

This will build a release build, with various compiler optimisation flags.

#### -DCMAKE_BUILD_TYPE=Debug

This will build a debug build.

#### -DSTATIC:bool=TRUE

With this option enabled, CMake will build a static binary.

## How it works

This tool maintains version numbers with 4 components:

   Component | Description
   ----------|-------------------
   Major     | The major version number of a project.
   Minor     | The minor version number of a project.
   Build     | The build number of a project, see below.
   Patch     | The patch, revsion, or service pack
   
Of special interest is the *build number*, which can be generated and
incremented using a few methods: 
   

### Simple incrementation

This is the most simple method whereby the build number is incremented
sequentially, i.e. a build number of 1 increments to 2, or a build number of
41 increments to 42. 
   

### Month offset incrementation

Otherwise known as the Microsoft Office method.  The build number is composed
using the following method: 
   
   1. Set a 'base year' for the project.
   2. Compute the difference in months between January 1st of the base year
      and the current month, this becomes the first group of digits. 
   3. Take the day number of the current month, this becomes the second group
      of digits.
   
For example, let us imagine we have a project started in 2003. This project
goes along quite nicely, and we're compiling it from source on October 17th,
2005, 34 months after the start year.  The build number would be 3417.  Or,
17th day of the 34th month after January 2003.


### Year offset incrementation

Otherwise known as the Microsoft Visual C++ compiler method. The build number
is composed using the following method:
   
   1. Set a 'base year' for the project.
   2. Compute the difference in years between the current year and the base
      year, this becomes the first group of digits.
   3. Add the two-digit month number for the current month.
   4. Add the two-digit day number for the current month.
   
For example, let us imagine we have a project started in 2005. This project
goes along quite nicely, and we're compiling it from source on September 4th,
2007.  2 years after the start year.  The build number would be 20904.


### Date incrementation

The second-simplest method, otherwise known as ISO 8601. The build number is
just the date encoded as yyyymmdd.


## Output

The verbuild tool can, as of right now, only handle output to C/C++ files, but
even then it has two ways of outputting information -- #define statements and
a structure.

Hopefully more output formats will be added in the near future.


## Input

The verbuild tool can parse existing headers for version information.  To see
what is required, please take a look at the CFormatting.hpp file.


## Flags and options

Usage:

    verbuild [-c] [-f <x.x.x.x>] [-g <basic|struct|doxygen|all>]
             [-i <simple|mydate|bymonths|byyears] [-o <string>] [-p <string>]
             [-t <c>] [-v] [-y <[1970...]>] [-V] [-D <number] [-h]

### General options

##### -h, --help
Show a help message.

##### -v, --version
Show version information..

### Increment options

##### -f, --format
The format string dictates how a version will be incremented and uses the form:
*<major>*.*<minor>*.*<build>*.*<patch>*

The options for each field are:

| Format | Description                      |
|--------|----------------------------------|
| *      | Number component is left as-is.  |
| +      | Number component is incremented. |
| [0-9]+ | Number component is a constant.  |

If this flag is not specified, then it will default to incrementing the build
field only.

As an example, if we have a format string of `10.*.+.*`, then the version number
will contain the following components:
   
| Component | Description                                      |
|-----------|--------------------------------------------------|
| 10        | The major version will always have the value 10. |
| *         | The minor number will be left as-is.             |
| +         | The build number will be incremented.            |
| *         | The patch number will be left as-is.             |
   
Therefore, if the version number is read in from a header as `5.5.8.1`, then
after processing, the format will result in a new version number of `10.5.9.1`.

##### -i, --increment
The increment algorithm to use.

##### -y, --year
The year used for calendar offset calculations.

If this flag is given with no argument, the year is set to the current year.

If this flag is not given, the year defaults to the current year.

### Transform options

##### -t, --transform
Select a transform to use when writing version information.

Transforms will write data in a structure usable by the language for which they
are written.

For example, the `c` transform will write a C header.

##### -p, --prefix
A string that is prepended to the symbols created by the transform module.

### Output options

##### -c, --create
If this flag is enabled, then the output file will be created if it does not
exist.

If this flag is not enabled, then an error will be signalled if the file does
not exist.

##### -g, --groups
Select what output groups are written to the output.

Each file is made up of various groups that have different purposes. These
groups include such things as putting version information into a data structure,
or a preprocessor definition, Doxygen documentation etc.

##### -o, --output
The file to which version information will be written.

### Information options

##### --list-groups
List all available groups for use with the `groups' option.

##### --list-increments
List all available increments for use with the `increments` option.

##### --list-transforms
List all available transforms for use with the `transform' option.

### Debug options

##### -V, --verbose
Enable verbose output.

##### -D, --debug
Enable debug messages.

The higher the level, the more verbose the debugging.

If this flag is given with no value, the level is set to 1; otherwise the level
is set to the given value.

If the flag is not given, then the level defaults to 0.


## Examples

The most basic of invocations is:

``` shell
verbuild -t c -g basic
```

which results in the following output to stdout:

``` c
/* ----------------------------------------------------
 * Automatically generated by VerBuild 1.0.601.2.
 * Do not edit by hand.
 * ----------------------------------------------------
 */

#ifndef __VersionInfo_Header__
#define __VersionInfo_Header__
    
#define VERSION_MAJOR      0
#define VERSION_MINOR      0
#define VERSION_BUILD      1
#define VERSION_PATCH      0
    
#define VERSION_BASE_YEAR  1970
#define VERSION_DATE       ""
#define VERSION_TIME       "12:11:19"
#define VERSION_STRING     "0.0.1.0"
    
#endif // !__VersionInfo_Header__
```

A more advanced example would be:

``` shell
verbuild -t c -y 2010 -i btyears -f 10.*.+.* -g struct
```

which yields:

``` c
/* ----------------------------------------------------
 * Automatically generated by VerBuild 1.0.601.2.
 * Do not edit by hand.
 * ----------------------------------------------------
 */
    
#ifndef __VersionInfo_Header__
#define __VersionInfo_Header__
    
static struct VersionNumber_s {
    int baseYear;
    int major;
    int minor;
    int build;
    int patch;
} VersionNumber = {
    2010,
    10,
    0,
    30601,
    0
};
    
#endif // !__VersionInfo_Header__
```

To deal with a file, one can use:

``` shell
verbuild -t c -y 2010 -i months -f 13.04.*.1 -g basic -g doxygen -o test.h -c
```

The resulting file will look like this:

``` c
/* ----------------------------------------------------
 * Automatically generated by VerBuild 1.0.601.2.
 * Do not edit by hand.
 * ----------------------------------------------------
 */
    
#ifndef __VersionInfo_Header__
#define __VersionInfo_Header__
    
/**
 * @file test.h
 * @author VarBuild 1.0.601.2
 * @brief Provides version information.
 */
    
/**
 * @def VERSION_MAJOR
 * @brief Major version number.
 *
 * @def VERSION_MINOR
 * @brief Minor version number.
 *
 * @def VERSION_BUILD
 * @brief Build number.
 *
 * @def VERSION_PATCH
 * @brief Patch number.
 *
 * @def VERSION_BASE_YEAR
 * @brief The year the project was started.
 *
 * @def VERSION_DATE
 * @brief The date this build was compiled.
 *
 * @def VERSION_TIME
 * @brief The time this build was compiled.
 *
 * @def VERSION_STRING
 * @brief String representation of the version.
 */
#define VERSION_MAJOR      13
#define VERSION_MINOR      4
#define VERSION_BUILD      0
#define VERSION_PATCH      1
    
#define VERSION_BASE_YEAR  2010
#define VERSION_DATE       ""
#define VERSION_TIME       "12:22:17"
#define VERSION_STRING     "13.4.0.1"
    
#endif // !__VersionInfo_Header__
```

You can also prefix the symbols generated thusly:
 
``` shell
verbuild -t c -g basic -p hello
```
     
which generates output similar to:
 
``` c
/*
 * ----------------------------------------------------
 * Automatically generated by VerBuild 1.1.601.0.
 * Do not edit by hand.
 * ----------------------------------------------------
 */
    
#pragma once
    
#ifndef __VersionInfo_Header__
#define __VersionInfo_Header__
    
#define HELLO_VERSION_MAJOR      0
#define HELLO_VERSION_MINOR      0
#define HELLO_VERSION_BUILD      1
#define HELLO_VERSION_PATCH      0
    
#define HELLO_VERSION_BASE_YEAR  1970
#define HELLO_VERSION_DATE       ""
#define HELLO_VERSION_TIME       "22:50:59"
#define HELLO_VERSION_STRING     "0.0.1.0"
    
#endif // !__VersionInfo_Header__
```

For an example on using verbuild with Windows resource files, see
`src\verbuild\resource.rc`.
