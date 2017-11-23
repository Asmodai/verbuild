Hi, Emacs: -*- mode: gfm -*-

verbuild
========

Version number auto-incrementing and build numbering tool.


Building From Source
====================

Requirements
------------

verbuild requires Boost 1.65.0 or later.  This might mean that you have to build
Boost from source on your system.

If there are Boost binaries provided for your system, you require at least the
following libraries:

  * program_options
  * date_time
  * unit_test_framework

CMake 2.6 or higher is required in order to build the software, though CMake
3.5.1 or higher is highly recommended.

You also require a C++ compiler that is capable of at least C++14.

verbuild has been tested with the following compilers:

 * GCC 5.4.0,
 * Microsoft Visual Studio 2017 with version 19.11.25547 of the compiler,
 * Clang **not yet**

Building
--------

To build verbuild on a Unix or Unix-like, issue the following commands:
``` shell
mkdir build
cd build
cmake ..
make
```
To build in Windows, either execute cmake in a similar manner from a shell, or
use cmake-gui.

If you wish to use Visual Studio 2017, then open the verbuild folder with
`Open > Folder`, then use the `CMake` menu to generate a cache
`CMake > Cache > Generate > CMakeLists.txt`, and then build the project via
`CMake > Build All`.

If you wish to run the tests, then on a Unix or Unix-like execute
``` shell
make test
```
or, if you prefer a more verbose output
``` shell
ctest --verbose
```

With Visual Studio, start the tests via `CMake > Run Tests > CMakeLists.txt`.


Contributing
============

You are welcome to contribute to this project, but please keep the following
guidelines in mind:

Indentation
-----------

Any code submitted for consideration must match the existing indentation scheme
used in the source code.  This is a modification of the One True Brace style,
and can be summarised thusly:

``` c++
namespace SomeNamespace
{

  static
  int
  some_standard_c_function(void *some_pointer,
                           int   some_value)
  {
    int   some_thing      = 12;
    void *another_pointer = nullptr;
    
    if (some_pointer == nullptr) {
      /* Complain loudly and send flames via email. */
    }
    
    if (some_value > 12 &&
        (some_value <= 41 || some_value == meaning_of_life))
    {
      /* Huh? */
    }
    
    /* some function body */
    
    return -12;
  }
  
  class SomeClass
    : public SomeInheritedClass
  {
  private:
    bool some_private_variable_;
      
  public:
    SomeClass();
    ~SomeClass();
    
    const bool &get_something() const;
    void        set_something(const bool);
    
    void do_something();
  };

  /* ... */
  
  void
  SomeClass::do_something()
  {
    switch (some_value) {
      case HERP:
        /* Do something. */
        break;
        
      case DERP:
        /* Do something else. */
        break;
        
      default:
        /* Uh oh. */
    }
  }

}
```

Header-only class implementations should strive for clarity, so that others do
not have to filter lots of text in order to see your interface.

Pull Requests
-------------

Pull requests without notification of some kind will probably go unnoticed for
several years.  This is a project with quite a low submission rate, so if you do
send a PR, please drop me an email.

PRs without descriptive commit messages will probably be rejected.

If the PR's intent is to fix a bug, please ensure the bug is listed in the issue
tracker first, and do not close an issue after submitting a PR as that is
something I will do should the PR be accepted.

Feature Requests
----------------

This project is intended to scratch a specific itch, but I am open to new ideas
-- within reason, this is a version building tool, not a programming language!

If you have an idea for an enhancement, please open an issue with the
*enhancement* label and drop me an email too.

Other requests will be evaluated on a case-by-case version.


Incrementing
============

This tool maintains version numbers with 4 components:

   Component | Description
   ----------|-------------------
   Major     | The major version number of a project.
   Minor     | The minor version number of a project.
   Build     | The build number of a project, see below.
   Patch     | The patch or the service pack
   
Of special interest is the build number, which can be generated and
incremented using a few methods: 
   

Simple incrementation
---------------------
This is the most simple method whereby the build number is incremented
sequentially, i.e. a build number of 1 increments to 2, or a build number of
41 increments to 42. 
   

Month offset incrementation
---------------------------
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


Year offset incrementation
--------------------------
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


Date incrementation
-------------------
The second-simplest method, otherwise known as ISO 8601. The build number is
just the date encoded as yyyymmdd.


Output
------
The verbuild tool can, as of right now, only handle output to C/C++ files, but
even then it has two ways of outputting information -- #define statements and
a structure.

Hopefully more output formats will be added in the near future.


Input
-----
The verbuild tool can parse existing headers for version information.  To see
what is required, please take a look at the CFormatting.hpp file.


Flags and options
-----------------
Usage:

    verbuild  [-c] [-f <x.x.x.x>] [-g <basic|struct|doxygen|all>] ...  [-i
              <simple|date|months|years>] [-o <string>] [-p <string>] [-s]
               -t <c> [-v] [-y <[1970...2013]>] [--] [--version] [-h]



Where:

    -c,  --create
      Create the output file if it does not exist.
 
    -f <x.x.x.x>,  --format <x.x.x.x>
      Version number format string.
      
    -g <basic|struct|doxygen|all>,  --groups <basic|struct|doxygen|all>
       (accepted multiple times)
      Output groups generated.
    
    -i <simple|date|months|years>,  --increment <simple|date|months|years>
      Type of increment used.
    
    -o <string>,  --output <string>
      File containing version information.
    
    -p <string>,  --prefix <string>
      String to prepend to symbols created by the formatter.
    
    -s,  --overflow
      Perform overflow checking and shifting.
    
    -t <c>,  --formatter <c>
      (required)  Output formatter type: c = C/C++
    
    -v,  --verbose
      Verbose output.
    
    -y <[1970...2013]>,  --base-year <[1970...2013]>
      The year the project was started.
    
    --,  --ignore_rest
      Ignores the rest of the labeled arguments following this flag.
    
    --version
      Displays version information and exits.
    
    -h,  --help
      Displays usage information and exits.



Format specifier
----------------
The format required for a version number is 'x.x.x.x', where x can be one of
the following:
   
   Format | Description
   -------|--------------------------------
   *      | Number component is left as-is.
   +      | Number component is incremented.
   [0-9]+ | Number component is a constant.
   
As an example, if we have a format string of `10.*.+.*`, then the version
number will contain the following components:
   
   Component | Description
   ----------|---------------------------
   10        | The major version will always have the value 10.
   *         | The minor number will be left as-is.
   +         | The build number will be incremented.
   *         | The patch number will be left as-is. 
   
Therefore, if the version number is read in from a header as `5.5.8.1`, then
after processing, the format will result in a new version number of
`10.5.9.1`.


Examples
--------

The most basic of invocations is:

    $ verbuild -t c -g basic

which results in the following output to stdout:

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


A more advanced example would be:

    $ verbuild -t c -y 2010 -i years -f 10.*.+.* -g struct

which yields:

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

To deal with a file, one can use:

    $ verbuild -t c -y 2010 -i months -f 13.04.*.1 -g basic -g doxygen -o test.h -c

The resulting file will look like this:

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

 You can also prefix the symbols generated thusly:
 
     verbuild -t c -g basic -p hello
     
 which generates output similar to:
 
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

For an example on using verbuild with Windows resource files, see
resource.rc.

