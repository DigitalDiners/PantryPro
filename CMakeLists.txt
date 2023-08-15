cmake_minimum_required(VERSION 3.3.2)
project(MyApp C CXX)
set(CMAKE_OSX_ARCHITECTURES x86_64)

# Find Boost
find_package(Boost REQUIRED COMPONENTS system)

# Print results for debugging
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")

# Include Boost headers
include_directories(${Boost_INCLUDE_DIRS})

# MySQL paths
set(MYSQLCPPCON_INCLUDE_DIR "/usr/local/mysql-connector-c++-8.1.0/include")
set(MYSQLCPPCON_LIB_DIR "/usr/local/mysql-connector-c++-8.1.0/lib64")

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

set(MYSQLCPPCONN_LIBRARY "/usr/local/mysql-connector-c++-8.1.0/lib64/libmysqlcppconn.9.dylib")
set(SSL_LIB "/usr/local/mysql-connector-c++-8.1.0/lib64/libssl.3.dylib")

target_link_libraries(MyApp ${MYSQLCPPCONN_LIBRARY} ${SSL_LIB} ${Boost_LIBRARIES}) 