cmake_minimum_required(VERSION 3.5)

project(PantryPro C CXX)

include(cmake/App.cmake)

set(SOURCES "src/MyApp.h"
            "src/MyApp.cpp"
            "src/main.cpp"
            )

add_app("${SOURCES}")

find_package(Catch2 REQUIRED)
add_executable(tests "tests/test.cpp")
target_link_libraries(tests PRIVATE Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(tests)