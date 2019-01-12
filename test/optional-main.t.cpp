// Copyright 2017-2018 by Martin Moene
//
// https://github.com/martinmoene/optional-bare
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "optional-main.t.hpp"

#define optional_PRESENT( x ) \
    std::cout << #x << ": " << x << "\n"

//#define optional_ABSENT( x )
//    std::cout << #x << ": (undefined)\n"

lest::tests & specification()
{
    static lest::tests tests;
    return tests;
}

CASE( "optional-bare version" "[.version]" )
{
    optional_PRESENT( optional_bare_MAJOR );
    optional_PRESENT( optional_bare_MINOR );
    optional_PRESENT( optional_bare_PATCH );
    optional_PRESENT( optional_bare_VERSION );
}

CASE( "optional-bare configuration" "[.optional][.config]" )
{
    optional_PRESENT( optional_HAVE_STD_OPTIONAL );
    optional_PRESENT( optional_USES_STD_OPTIONAL );
    optional_PRESENT( optional_OPTIONAL_DEFAULT );
    optional_PRESENT( optional_OPTIONAL_NONSTD );
    optional_PRESENT( optional_OPTIONAL_STD );
    optional_PRESENT( optional_CONFIG_SELECT_OPTIONAL );
    optional_PRESENT( optional_CONFIG_NO_EXCEPTIONS );
    optional_PRESENT( optional_CPLUSPLUS );
}

CASE( "__cplusplus" "[.stdc++]" )
{
    optional_PRESENT( __cplusplus );
}

CASE( "compiler version" "[.compiler]" )
{
#if optional_USES_STD_OPTIONAL
    std::cout << "(Compiler version not available: using std::optional)\n";
#else
    std::cout << "(Compiler version not available with optional bare, nonstd::optional)\n";
//    optional_PRESENT( optional_COMPILER_CLANG_VERSION );
//    optional_PRESENT( optional_COMPILER_GNUC_VERSION );
//    optional_PRESENT( optional_COMPILER_MSVC_VERSION );
#endif
}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include -o optional-main.t.exe optional-main.t.cpp && optional-main.t.exe --pass
g++ -std=c++98 -I../include -o optional-main.t.exe optional-main.t.cpp && optional-main.t.exe --pass
g++ -std=c++03 -I../include -o optional-main.t.exe optional-main.t.cpp && optional-main.t.exe --pass
g++ -std=c++0x -I../include -o optional-main.t.exe optional-main.t.cpp && optional-main.t.exe --pass
g++ -std=c++11 -I../include -o optional-main.t.exe optional-main.t.cpp && optional-main.t.exe --pass
g++ -std=c++14 -I../include -o optional-main.t.exe optional-main.t.cpp && optional-main.t.exe --pass
g++ -std=c++17 -I../include -o optional-main.t.exe optional-main.t.cpp && optional-main.t.exe --pass

cl -EHsc -I../include optional-main.t.cpp && optional-main.t.exe --pass
#endif

// end of file
