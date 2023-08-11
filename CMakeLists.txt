project(MyApp C CXX)
cmake_minimum_required(VERSION 3.3.2)

# Find Boost
find_package(Boost REQUIRED)
set(BOOST_INCLUDE_DIR "C:/Users/joshl/Boost/boost_1_82_0")
include_directories(${BOOST_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

# MySQL paths
set(MYSQL_CONNECTOR_INCLUDE_DIR "C:/Program Files/MySQL/MySQL Connector C++ 1.1.12/include")
set(MYSQL_LIB_DIR "C:/Program Files/MySQL/MySQL Server 8.1/lib")
set(MYSQLCPPCONN_LIB_DIR "C:/Program Files/MySQL/MySQL Connector C++ 1.1.12/lib/opt")

# Include header files
include_directories(${MYSQL_CONNECTOR_INCLUDE_DIR})

# Link library directories
link_directories(${MYSQL_LIB_DIR} ${MYSQLCPPCONN_LIB_DIR})

include(cmake/App.cmake)

set(SOURCES "src/MyApp.h"
            "src/MyApp.cpp"
            "src/main.cpp"
            "src/dbconnection.h"
            "src/dbconnection.cpp")

add_app("${SOURCES}")

find_library(MYSQL_LIBRARY
             NAMES mysqlclient
             PATHS ${MYSQL_LIB_DIR})

find_library(MYSQLCPPCONN_LIBRARY
            NAMES mysqlcppconn
            PATHS ${MYSQLCPPCONN_LIB_DIR})

# Link Boost and MySQL libraries
target_link_libraries(MyApp ${Boost_LIBRARIES}) 
target_link_libraries(MyApp ${MYSQLCPPCONN_LIBRARY})
target_link_libraries(MyApp ${MYSQL_LIBRARY})

