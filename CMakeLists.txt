# Copyright 2017-2018 by Martin Moene
#
# https://github.com/martinmoene/optional-bare
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required( VERSION 3.5 )

# optional-bare project and version, updated by script/update-version.py:

project(
    optional_bare
    VERSION 1.0.0
    DESCRIPTION "A simple version of a C++17-like optional for default-constructible, copyable types, for C++98 and later in a single-file header-only library"
#   HOMEPAGE_URL "https://github.com/martinmoene/optional-bare"
    LANGUAGES CXX )

set( ${PROJECT_NAME}_version "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}" )

# Toplevel or subproject:

if ( CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR )
    set( optional_IS_TOPLEVEL_PROJECT TRUE )
else()
    set( optional_IS_TOPLEVEL_PROJECT FALSE )
endif()

# If toplevel project, enable building and performing of tests, disable building of examples:

option( OPTIONAL_BARE_OPT_BUILD_TESTS    "Build and perform optional-bare tests" ${optional_IS_TOPLEVEL_PROJECT} )
option( OPTIONAL_BARE_OPT_BUILD_EXAMPLES "Build optional-bare examples" OFF )

option( OPTIONAL_BARE_OPT_SELECT_STD     "Select std::optional"    OFF )
option( OPTIONAL_BARE_OPT_SELECT_NONSTD  "Select nonstd::optional" OFF )

include( GNUInstallDirs )

set( package_name "optional-bare" )
set( include_source_dir "${PROJECT_SOURCE_DIR}/include" )

# Interface library:

add_library(
    ${package_name} INTERFACE )

target_include_directories(
    ${package_name} INTERFACE "$<BUILD_INTERFACE:${include_source_dir}>" )

# Installation:

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )

# If requested, build and perform tests, build examples:

enable_testing()

if ( OPTIONAL_BARE_OPT_BUILD_TESTS )
    add_subdirectory( test )
endif()

if ( OPTIONAL_BARE_OPT_BUILD_EXAMPLES )
    add_subdirectory( example )
endif()

# end of file
