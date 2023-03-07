cmake_minimum_required(VERSION 3.14)
set(NAME sv_list)

project(${NAME}
    VERSION 1.0.0
    DESCRIPTION "C++17 lib for string_view concatenation"
    LANGUAGES CXX)

add_library(${NAME} STATIC)

set_target_properties(${NAME} PROPERTIES
   CXX_STANDARD 17
   CXX_EXTENSIONS OFF
)

option(BUILD_TESTS "Build tests" OFF)

include_directories(include/)
target_sources(${NAME} PRIVATE src/string_view_list.cpp)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
