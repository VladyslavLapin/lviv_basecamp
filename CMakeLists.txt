cmake_minimum_required(VERSION 3.8.2)

project(Searcher VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Threads REQUIRED)

add_library(search)
target_sources(search PUBLIC ${CMAKE_SOURCE_DIR}/src/search.cpp)

add_executable(Searcher main.cpp)

target_link_libraries(Searcher PUBLIC Threads::Threads search)
target_include_directories(Searcher PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "include/"
                          "${CMAKE_SOURCE_DIR}/lib"
                          )