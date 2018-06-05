// Copyright 2017-2018 by Martin Moene
//
// https://github.com/martinmoene/optional-bare
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "optional-bare.t.h"

#if defined(_MSC_VER) && !defined(__clang__)
# define optional_COMPILER_MSVC_VERSION   (_MSC_VER / 100 - 5 - (_MSC_VER < 1900))
#else
# define optional_COMPILER_MSVC_VERSION   0
#endif

#if defined __GNUC__
# define optional_COMPILER_GNUC_VERSION  __GNUC__
#else
# define optional_COMPILER_GNUC_VERSION    0
#endif

#define optional_PRESENT( x ) \
    std::cout << #x << ": " << x << "\n"

#define optional_ABSENT( x ) \
    std::cout << #x << ": (undefined)\n"

lest::tests & specification()
{
    static lest::tests tests;
    return tests;
}

CASE( "__cplusplus" "[.stdc++]" )
{
    optional_PRESENT( __cplusplus );
}

CASE( "optional-bare version" "[.version]" )
{
    optional_PRESENT( optional_bare_VERSION );
}

CASE( "compiler version" "[.compiler]" )
{
#if optional_COMPILER_GNUC_VERSION
    optional_PRESENT( optional_COMPILER_GNUC_VERSION );
#else
    optional_ABSENT(  optional_COMPILER_GNUC_VERSION );
#endif

#if optional_COMPILER_MSVC_VERSION
    optional_PRESENT( optional_COMPILER_MSVC_VERSION );
#else
    optional_ABSENT(  optional_COMPILER_MSVC_VERSION );
#endif
}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include/nonstd -o optional-bare.t.exe optional-bare.t.cpp && optional-bare.t.exe --pass
g++ -std=c++98 -I../include/nonstd -o optional-bare.t.exe optional-bare.t.cpp && optional-bare.t.exe --pass
g++ -std=c++03 -I../include/nonstd -o optional-bare.t.exe optional-bare.t.cpp && optional-bare.t.exe --pass
g++ -std=c++0x -I../include/nonstd -o optional-bare.t.exe optional-bare.t.cpp && optional-bare.t.exe --pass
g++ -std=c++11 -I../include/nonstd -o optional-bare.t.exe optional-bare.t.cpp && optional-bare.t.exe --pass
g++ -std=c++14 -I../include/nonstd -o optional-bare.t.exe optional-bare.t.cpp && optional-bare.t.exe --pass
g++ -std=c++17 -I../include/nonstd -o optional-bare.t.exe optional-bare.t.cpp && optional-bare.t.exe --pass

cl -EHsc -I../include/nonstd optional-bare.t.cpp && optional-bare.t.exe --pass
#endif

// end of file
