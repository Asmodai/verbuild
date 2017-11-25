Hi Emacs, this is -*- mode: gfm -*-

# Contributing to Verbuild

## Table of Contents

  * [Contributing to Verbuild](#contributing-to-verbuild)
    * [Code of Conduct](#code-of-conduct)
    * [Do I have to read this?](#do-i-have-to-read-this)
    * [What should I know before I get started?](#what-should-i-know-before-i-get-started)
      * [Requirements](#requirements)
      * [CMake](#cmake)
        * [Windows](#windows)
        * [macOS](#macos)
        * [GNU/Linux](#gnulinux)
        * [Visual Studio 2017](#visual-studio-2017)
      * [boost](#boost)
        * [GNU/Linux](#gnulinux-1)
        * [Windows](#windows-1)
    * [How can I contribute?](#how-can-i-contribute)
      * [Reporting Bugs](#reporting-bugs)
      * [Feature requests](#feature-requests)
      * [Pull Requests](#pull-requests)
    * [Style Guides](#style-guides)
      * [Git Commit Messages](#git-commit-messages)
      * [C   Style Guide](#c-style-guide)
      * [Documentation Style Guide](#documentation-style-guide)

## Code of Conduct

This project and everyone participating in it is coverned by the [Contributor
Covenant Code of Conduct](CODE_OF_CONDUCT.md).  By participating, you are
expected to uphold this code.  Please report unacceptable behaviour
to [asmodai@gmail.com](mailto:asmodai@gmail.com).

## Do I have to read this?
> **note:** Please do *not* file an issue to ask a question.  You will get
> faster results by emailing the author.

## What should I know before I get started?

### Requirements

#### CMake
Verbuild uses [CMake](https://cmake.org/) as its build management system.  You
will require CMake 3.6 or later installed.

##### Windows
If you are using Windows, you can download binaries from the CMake website.

##### macOS
You can obtain CMake binaries from the CMake website and either use `cmake` from
Terminal.app, or use the CMake GUI application.

##### GNU/Linux
Most GNU/Linux distributions have CMake available via package manager, or you
can build from source.

##### Visual Studio 2017
If you wish to use Visual Studio 2017, then open the verbuild folder with
`Open > Folder`, then use the `CMake` menu to generate a cache via `CMake > Cache >
Generate > CMakeLists.txt`, and then build the project via `CMake > Build All`.

You will need to use the `Change CMake settings` option and make changes to
`CMakeSettings.json` in order to have CMake locate dependencies.

As an example:

``` json
{
  "environments": [
    {
      "BOOST_ROOT": "C:/path/to/boost",
      "GIT_EXECUTABLE": "c:/path/to/git/bin/git.exe",
      "GIT_ROOT": "c:/path/to/git",
      "FLTK_ROOT": "c:/path/to/fltk"
    }
  ],
  "variables": [
    {
      "name": "BOOST_ROOT",
      "value": "C:/path/to/boost",
    },
    {
      "name": "FLTK_ROOT",
      "value": "c:/path/to/fltk"
    }
  ],
  "configurations": [
    {
      "name": "x86-Debug",
      "generator": "Ninja",
      "configurationType": "Debug",
      ...
    }
  ]
}
```

#### boost
Verbuild requires [Boost](https://www.boost.org/) 1.65.0 or greater to be
installed.  This means that you might have to build Boost from source on your
system in such a way that CMake can locate it.

##### GNU/Linux
Some distributions of GNU/Linux appear to only provide Boost 1.55.  You will
need to make sure that your distribution provides 1.65.0 or higher.

##### Windows
You will need to make sure that `BOOST_ROOT` is set to the right path before
CMake will locate it.

## How can I contribute?

### Reporting Bugs

If you find a bug, please use
the [issue tracker](https://github.com/Asmodai/verbuild/issues) to report a
bug.

Please give as much information as possible, including output from the program
executed with the following flags:
`verbuild -V -D 9 ...`

Also be sure to provide information on your operating system and architecture
(i.e. Ubuntu 16.04.03 LTS, AMD64).

If you compiled from source, please provide the name and version of your
compiled too.

### Feature requests

This project is intended to scratch a specific itch, but I am open to new ideas
-- within reason, this is a version building tool, not a programming language!

If you have an idea for an enhancement, please open an issue with the
*enhancement* label.

Other requests will be evaluated on a case-by-case version.

### Pull Requests

Please ensure to consider the following when opening a pull request:
 * Do *not* include issue numbers in the PR title.
 * Follow the [C++ style guide](#c-style-guide).
 * Follow the [documentation style guide](#documentation-style-guide).
 * Ensure you have written tests.
 * End **all** files with a newline.
 
## Style Guides
 
### Git Commit Messages
 * Use the present tense ("Add feature", not "Added feature")
 * Use the imperative mood ("Move thing to..." not "Moves thing to...")
 * Limit the first line to 50 characters or less.
 * Reference issues and pull requests *after* the first line.
 * Install the git hooks in `git-hooks\`.
 * Do **not** use emoji in either the title or message.
 
### C++ Style Guide

You may use
the [Google C++ style guide](https://google.github.io/styleguide/cppguide.html)
for inspiration, but the primary aim should be *consistency*.  If your code
looks like my code, then that's a good start.

I primarily use a mix of *BSD-style* and *One True Brace*.  For example,
consider the following code:

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
    
    const std::string &get_something() const;
    void               set_something(const std::string &);
    
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

### Documentation Style Guide

> It isn't news that developers don't like documenting their code. But you have
> good reason not to. And if you are documenting code, try to stop! It's not too
> late.

The only thing that ought to be documented is an API.  Verbuild is not an API.
Please do not use comment blocks to describe functions.

Comments should be used to describe intent when something is non-obvious.
Anything more and the code runs the risk of not having documentation that
accurately describes what is taking place.


