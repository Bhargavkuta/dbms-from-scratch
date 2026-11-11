cmake_minimum_required(VERSION 3.20)

project(AstraDB
    VERSION 0.1.0
    DESCRIPTION "A relational database management system built from scratch"
    LANGUAGES CXX
)

# Default to Debug on single-config generators (Ninja, MinGW Makefiles, Unix Makefiles)
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type (Debug, Release, RelWithDebInfo, MinSizeRel)" FORCE)
endif()

# Generate compile_commands.json for IDE/editor tooling (clangd, VS Code, etc.)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project-wide C++20 standard settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build options
option(ASTRA_BUILD_TESTS "Build AstraDB test suite" ON)
option(ASTRA_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

# Dedicated warning interface target so strict flags stay internal to AstraDB targets
# and do not leak into third-party dependencies (e.g., GoogleTest).
add_library(astra_warnings INTERFACE)
if(MSVC)
    target_compile_options(astra_warnings INTERFACE /W4 /permissive-)
    if(ASTRA_WARNINGS_AS_ERRORS)
        target_compile_options(astra_warnings INTERFACE /WX)
    endif()
else()
    target_compile_options(astra_warnings INTERFACE -Wall -Wextra -Wpedantic)
    if(ASTRA_WARNINGS_AS_ERRORS)
        target_compile_options(astra_warnings INTERFACE -Werror)
    endif()
endif()

# Core database engine library.
# Future subsystems (lexer, parser, ast, catalog, storage, index, execution, txn, wal)
# will plug into this target (or link as sub-libraries into it).
add_library(astra_core STATIC
    src/version.cpp
)

target_include_directories(astra_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(astra_core PUBLIC cxx_std_20)

target_compile_definitions(astra_core
    PRIVATE
        ASTRA_VERSION_STRING="${PROJECT_VERSION}"
)

target_link_libraries(astra_core
    PRIVATE
        astra_warnings
)

# CLI shell executable
add_executable(astra
    src/main.cpp
)

target_link_libraries(astra
    PRIVATE
        astra_core
        astra_warnings
)

# Testing (CTest)
include(CTest)
if(ASTRA_BUILD_TESTS AND BUILD_TESTING)
    add_subdirectory(tests)
endif()
