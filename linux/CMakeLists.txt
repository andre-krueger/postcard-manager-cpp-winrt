cmake_minimum_required(VERSION 3.5.1)

project(postcard-manager)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
  ../core/src/sqlite_connection.cpp)
set(SOURCES
  ../core/include/sqlite_connection.hpp)

add_library(core SHARED ${SOURCES} ${HEADERS})
set_target_properties(core PROPERTIES LINKER_LANGUAGE CXX)
