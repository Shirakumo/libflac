cmake_minimum_required(VERSION 3.1)
project(flac)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

## Main Library
include_directories("src/")
file(GLOB lib_src "src/*.c")
add_library(flac SHARED ${lib_src})
set_property(TARGET flac PROPERTY C_STANDARD 99)
set_property(TARGET flac PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(flac PRIVATE FLAC_BUILD=1)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang"
    OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  target_compile_options(flac PRIVATE -fvisibility=hidden)
endif()

## Warnings
if(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")
  add_definitions(/W2)
elseif(CMAKE_BUILD_TOOL MATCHES "(gcc|clang)")
  add_definitions(-W -Wall -Wextra -pedantic)
endif()
add_definitions(-Wno-ignored-attributes)

install(TARGETS flac DESTINATION /usr/local/lib)
