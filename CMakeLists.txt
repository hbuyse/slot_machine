cmake_minimum_required(VERSION 3.0)
project(slot_machine_simulator VERSION 1.0.0 LANGUAGES C)

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)
string(LENGTH ${PROJECT_NAME} PROJECT_NAME_LENGTH)

set(PROJECT_NAME_UNDERLINE "")
foreach(i RANGE 1 ${PROJECT_NAME_LENGTH})
    string(CONCAT PROJECT_NAME_UNDERLINE ${PROJECT_NAME_UNDERLINE} "=")
endforeach(i)

set(PROJECT_DESCRIPTION "Slot machine simulator in C")

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_VERBOSE_MAKEFILE off)

# check_include_files
include(CheckIncludeFiles)

# CMAKE_INSTALL_LIBDIR, CMAKE_INSTALL_INCLUDEDIR, CMAKE_INSTALL_DATAROOTDIR
include(GNUInstallDirs)

# check_symbol_exists
include(CheckSymbolExists)

# Check if functions exists
include(CheckFunctionExists)

check_include_files(inttypes.h HAVE_INTTYPES_H)
check_include_files(stdint.h HAVE_STDINT_H)
check_include_files(stdio.h HAVE_STDIO_H)
check_include_files(stdlib.h HAVE_STDLIB_H)
check_include_files(string.h HAVE_STRING_H)

#For the shared library:
link_directories(${CMAKE_CURRENT_BINARY_DIR})

option(BUILD_DOCS "Build documentation" ON)
option(EASTER_EGG "Build with easter egg" OFF)

if (EASTER_EGG)
  add_definitions(-DEASTER_EGG)
endif (EASTER_EGG)

# EXECUTABLE
include(src/CMakeLists.txt)

# Documentation
if(BUILD_DOCS)
    include(docs/CMakeLists.txt)
endif(BUILD_DOCS)