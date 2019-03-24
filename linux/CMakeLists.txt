cmake_minimum_required(VERSION 3.5.1)

project(postcard-manager)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
  ../core/src/sqlite_connection.cpp
  ../core/src/database_service.cpp
  ../core/src/location_repository.cpp)
set(HEADERS
  ../core/include/database_service.hpp
  ../core/include/sqlite_connection.hpp
  ../core/include/location_repository.hpp
  ../core/include/models.hpp)

add_library(core SHARED ${SOURCES} ${HEADERS})
set_target_properties(core PROPERTIES LINKER_LANGUAGE CXX)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../core/include)
target_link_libraries(core sqlite3)

set(UNIT_TESTS_SOURCES)

set(INTEGRATION_TESTS_SOURCES
  ../core/tests/integration/test_location_repository.cpp
  ../core/tests/integration/test_sqlite_connection.cpp
  ../core/tests/integration/test_database_service.cpp
        )

include (CTest)
enable_testing()
find_package(GTest MODULE REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
#add_executable(unit-tests ${UNIT_TESTS_SOURCES})
add_executable(integration-tests ${INTEGRATION_TESTS_SOURCES})
#target_link_libraries(unit-tests PRIVATE core)
target_link_libraries(integration-tests PRIVATE core)
# This requires an up-to-date gcc and a vcpkg that was compiled with this gcc version
#target_link_libraries(unit-tests PRIVATE stdc++fs)
#target_link_libraries(unit-tests PRIVATE ${GTEST_BOTH_LIBRARIES})
target_link_libraries(integration-tests PRIVATE stdc++fs)
target_link_libraries(integration-tests PRIVATE ${GTEST_BOTH_LIBRARIES})
#add_test(unit unit-tests)
add_test(integration integration-tests)
