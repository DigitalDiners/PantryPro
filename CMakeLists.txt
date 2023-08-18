cmake_minimum_required(VERSION 3.5)
project(PantryPro C CXX)
set(CMAKE_OSX_ARCHITECTURES x86_64)

find_package(Boost 1.72.0 REQUIRED)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

#message(STATUS "BOOST_INCLUDE_DIR: ${BOOST_INCLUDE_DIR}")

# MySQL paths
set(MYSQLCPPCON_INCLUDE_DIR "mysql-connector-c++-8.1.0/include")
set(MYSQLCPPCON_LIB_DIR "mysql-connector-c++-8.1.0/lib64")

# Include header files
include_directories(${MYSQLCPPCON_INCLUDE_DIR})

# Link library directories
link_directories(${MYSQLCPPCON_LIB_DIR})

# Print results for debugging
message(STATUS "MYSQLCPPCON_INCLUDE_DIRS: ${MYSQLCPPCON_INCLUDE_DIR}")
message(STATUS "MYSQLCPPCON_LIBRARIES: ${MYSQLCPPCON_LIB_DIR}")

# Setting RPATH
set(CMAKE_INSTALL_RPATH "${MYSQLCPPCON_LIB_DIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

include(cmake/App.cmake)

set(SOURCES "src/MyApp.h"
            "src/MyApp.cpp"
            "src/databaseConnection.h"
            "src/databaseConnection.cpp"
            "src/main.cpp")

add_app("${SOURCES}")

set(MYSQLCPPCONN_LIBRARY "libmysqlcppconn.9.dylib")
set(SSL_LIB "libssl.3.dylib")

target_link_libraries(PantryPro ${MYSQLCPPCONN_LIBRARY} ${SSL_LIB} ${Boost_LIBRARIES})

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests "tests/test.cpp")
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
