optional bare - A simple single-file header-only version of a C++17-like optional for default-constructible, copyable types, for C++98 and later
====================================================
[![Language](https://img.shields.io/badge/language-C++-blue.svg)](https://isocpp.org/)  [![Standard](https://img.shields.io/badge/c%2B%2B-98-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT) [![Build Status](https://travis-ci.org/martinmoene/optional-bare.svg?branch=master)](https://travis-ci.org/martinmoene/optional-bare) [![Build status](https://ci.appveyor.com/api/projects/status/xl1lrm4cfdi08431?svg=true)](https://ci.appveyor.com/project/martinmoene/optional-bare) [![Version](https://badge.fury.io/gh/martinmoene%2Foptional-bare.svg)](https://github.com/martinmoene/optional-bare/releases) [![download](https://img.shields.io/badge/latest%20version%20%20-download-blue.svg)](https://raw.githubusercontent.com/martinmoene/optional-bare/master/include/nonstd/optional.hpp) [![Try it online](https://img.shields.io/badge/try%20it-online-blue.svg)](https://wandbox.org/permlink/YAWZ1gyu1zDFGh9V)

**Contents**  
- [Example usage](#example-usage)
- [In a nutshell](#in-a-nutshell)
- [License](#license)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Synopsis](#synopsis)
- [Building the tests](#building-the-tests)
- [Notes and references](#notes-and-references)
- [Appendix](#appendix)


Example usage
-------------
```C++
#include "optional.hpp"

#include <cstdlib>
#include <iostream>

using nonstd::optional;
using nonstd::nullopt;

optional<int> to_int( char const * const text )
{
    char * pos = NULL;
    const int value = strtol( text, &pos, 0 );

    return pos == text ? nullopt : optional<int>( value );
}

int main( int argc, char * argv[] )
{
    char * text = argc > 1 ? argv[1] : "42";

    optional<int> oi = to_int( text );

    if ( oi ) std::cout << "'" << text << "' is " << *oi;
    else      std::cout << "'" << text << "' isn't a number";
}
```
### Compile and run
```
prompt>g++ -Wall -Wextra -std=c++03 -I.. -o to_int.exe to_int.cpp && to_int x1
'x1' isn't a number
```
In a nutshell
---------------
**optional bare** is a single-file header-only library to represent optional (nullable) objects and pass them by value. The library aims to provide a [C++17-like optional](http://en.cppreference.com/w/cpp/utility/optional) for default-constructible and copyable types for use with C++98 and later. *optional bare* is derived from [optional lite](https://github.com/martinmoene/optional-lite).

**Features and properties of optional bare** are ease of installation (single header), freedom of dependencies other than the standard library.

**Not provided** are `emplace()` or other operations that require move semantics. *optional bare* does not support reference-type optionals and it does not handle overloaded *address of* operators.

For more examples, see [this answer on StackOverflow](http://stackoverflow.com/a/16861022) [6] and the [quick start guide](http://www.boost.org/doc/libs/1_57_0/libs/optional/doc/html/boost_optional/quick_start.html) [7] of Boost.Optional (note that its interface differs from *optional bare*).


License
-------
*optional bare* uses the [MIT](LICENSE) license.
 

Dependencies
------------
*optional bare* has no other dependencies than the [C++ standard library](http://en.cppreference.com/w/cpp/header).


Installation
------------
*optional bare* is a single-file header-only library. Put `optional.hpp` in the [include](include) folder directly into the project source tree or somewhere reachable from your project.


Synopsis
--------
For the interface of `std::optional`, see [cppreference](http://en.cppreference.com/w/cpp/utility/optional).

*optional bare* uses C++98 only, it does not differentiate its compatibility with `std::optional` based on compiler and standard library support of C++11 and later. *optional bare* does not control whether functions participate in overload resolution based on the value type.

The following table gives an overview of what is **not provided** by *optional bare*.

| Kind | Item             | Remark |
|------|------------------|--------|
| Types| in_place_t       |move-semantics not supported|
|&nbsp;| in_place_type_t  |&nbsp;|
|&nbsp;| in_place_index_t |&nbsp;|
| Tags | in_place         |&nbsp;|
|&nbsp;| in_place_type    |&nbsp;|
|&nbsp;| in_place_index   |&nbsp;|
| Member functions |&nbsp;|&nbsp;| 
| &emsp;Construction | optional( optional&& other ) |&nbsp;|
|&nbsp;| template &lt;class U><br>optional( optional&lt;U>&& other ) |&nbsp;|
|&nbsp;| template&lt;class U = value_type><br>optional( U&& value ) |provides optional( T const & )|
|&nbsp;| template&lt;...><br>optional( std::in_place_t, ...) |&nbsp;|
| &emsp;Assignment | optional & operator=( optional&& other ) |&nbsp;|
|&nbsp;| template &lt;class U><br>optional & operator=( optional&lt;U>&& other ) |&nbsp;|
|&nbsp;| template&lt;class U = value_type><br>optional & operator=( U&& value ) |provides operator=( T const & )|
| &emsp;Modifiers | template&lt;...><br>T& emplace(...)  | move-semantics not supported |
| Non-member functions | template&lt;...><br>optional&lt;T> make_optional(  ... && ) |no forwarding, only provides<br>make_optional( T const & )|
| Other | std::hash&lt;nonstd::optional> | std::hash<> requires C++11|


Building the tests
------------------
To build the tests you need:

- [CMake](http://cmake.org), version 2.8.12 or later to be installed and in your PATH.
- A compiler that supports C++98 or later.

The [*lest* test framework](https://github.com/martinmoene/lest)  is included in the [test folder](test).

The following steps assume that the [*optional bare* source code](https://github.com/martinmoene/optional-bare) has been cloned into a directory named `c:\optional-bare`.

1. Create a directory for the build outputs for a particular architecture.
Here we use c:\optional-bare\build-win-x86-vc10.

        cd c:\optional-bare
        md build-win-x86-vc10
        cd build-win-x86-vc10

2. Configure CMake to use the compiler of your choice (run `cmake --help` for a list).

        cmake -G "Visual Studio 10 2010" ..

3. Build the test suite in the Debug configuration (alternatively use Release).    

        cmake --build . --config Debug

4. Run the test suite.    

        ctest -V -C Debug

All tests should pass, indicating your platform is supported and you are ready to use *optional bare*.


Notes and references
--------------------
[1] CppReference. [Optional](http://en.cppreference.com/w/cpp/utility/optional).  

[2] ISO/IEC WG21. [N4606, section 20.6 Optional objects](http://wg21.link/n4606). July 2016.

[3] Fernando Cacciola, Andrzej Krzemieński. [A proposal to add a utility class to represent optional objects (Revision 5)](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3793.html).

[4] Andrzej Krzemieński. [optional (nullable) objects for C++14](https://github.com/akrzemi1/Optional). Reference implementation on GitHub.

[5] Fernando Cacciola. [Boost.Optional library](http://www.boost.org/doc/libs/1_49_0/libs/optional/doc/html/index.html).

[6] StackOverflow. [How should one use std::optional?](http://stackoverflow.com/a/16861022). Answer by Timothy Shields. 31 May 2013.

[7] Fernando Cacciola. [Boost.Optional Quick start guide](http://www.boost.org/doc/libs/1_57_0/libs/optional/doc/html/boost_optional/quick_start.html).


Appendix
--------
### A.1 Optional Bare test specification

```
optional: Allows to default construct an empty optional
optional: Allows to explicitly construct a disengaged, empty optional via nullopt
optional: Allows to copy-construct from empty optional
optional: Allows to copy-construct from non-empty optional
optional: Allows to copy-construct from literal value
optional: Allows to copy-construct from value
optional: Allows to copy-construct from optional with different value type
optional: Allows to assign nullopt to disengage
optional: Allows to copy-assign from/to engaged and disengaged optionals
optional: Allows to copy-assign from literal value
optional: Allows to copy-assign from value
optional: Allows to copy-assign from optional with different value type
optional: Allows to swap with other optional (member)
optional: Allows to obtain pointer to value via operator->()
optional: Allows to obtain value via operator*()
optional: Allows to obtain engaged state via has_value()
optional: Allows to obtain has_value() via operator bool()
optional: Allows to obtain value via value()
optional: Allows to obtain value or default via value_or()
optional: Throws bad_optional_access at disengaged access
optional: Allows to reset content
optional: Allows to swap engage state and values (non-member)
optional: Provides relational operators
make_optional: Allows to copy-construct optional
```
