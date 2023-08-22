cmake_minimum_required(VERSION 3.5)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

project(PantryPro C CXX)

include(cmake/App.cmake)

set(SOURCES "src/MyApp.h"
            "src/MyApp.cpp"
            "src/main.cpp"
            )

add_app("${SOURCES}")

option(BUILD_TESTING "Builds only the test executable." OFF)

if(BUILD_TESTING)
  include(FetchContent)

  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.0.1 # or a later release
  )

  FetchContent_MakeAvailable(Catch2)

  add_executable(tests "tests/test.cpp")
  add_executable(UnitTests "tests/RecipeTests.cpp")

  target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
  target_link_libraries(UnitTests PRIVATE Catch2::Catch2WithMain)
endif()