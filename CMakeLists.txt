cmake_minimum_required(VERSION 3.5)
project(PantryPro C CXX)
set(CMAKE_OSX_ARCHITECTURES x86_64)

# Set the base directory based on the current source directory
set(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# MySQL paths using the BASE_DIR variable
set(MYSQLCPPCON_INCLUDE_DIR "${BASE_DIR}/mysql-connector-c++-8.1.0/include")
set(MYSQLCPPCON_LIB_DIR "${BASE_DIR}/mysql-connector-c++-8.1.0/lib64")

# Include header files
include_directories(${MYSQLCPPCON_INCLUDE_DIR})

# Full paths for libraries
set(MYSQLCPPCONN_LIBRARY "${MYSQLCPPCON_LIB_DIR}/libmysqlcppconn.9.dylib")
set(SSL_LIB "${MYSQLCPPCON_LIB_DIR}/libssl.3.dylib")

include(cmake/App.cmake)

set(SOURCES "src/MyApp.h"
            "src/MyApp.cpp"
            "src/databaseConnection.h"
            "src/recipeDatabase.h"
            "src/recipe.h"
            "src/recipeDatabase.cpp"
            "src/databaseConnection.cpp"
            "src/recipe.cpp"
            "src/main.cpp")

add_app("${SOURCES}")

# Setting RPATH
set_target_properties(PantryPro PROPERTIES
    INSTALL_RPATH "@executable_path"
)

target_link_libraries(PantryPro ${MYSQLCPPCONN_LIBRARY} ${SSL_LIB})

# Add libcrypto.3.dylib to the list of dylibs to be copied
set(CRYPTO_LIB "${MYSQLCPPCON_LIB_DIR}/libcrypto.3.dylib")
set(DYLIBS ${MYSQLCPPCONN_LIBRARY} ${SSL_LIB} ${CRYPTO_LIB})
foreach(dylib ${DYLIBS})
    add_custom_command(TARGET PantryPro POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${dylib}
        $<TARGET_FILE_DIR:PantryPro>
    )
endforeach()

# Adjusting library paths inside the dylibs
add_custom_command(TARGET PantryPro POST_BUILD
    COMMAND install_name_tool -change "libcrypto.3.dylib" "@executable_path/libcrypto.3.dylib" $<TARGET_FILE_DIR:PantryPro>/libssl.3.dylib
    COMMAND install_name_tool -change "libcrypto.3.dylib" "@executable_path/libcrypto.3.dylib" $<TARGET_FILE_DIR:PantryPro>/libmysqlcppconn.9.dylib
    COMMAND install_name_tool -change "libssl.3.dylib" "@executable_path/libssl.3.dylib" $<TARGET_FILE_DIR:PantryPro>/libmysqlcppconn.9.dylib
)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests "tests/test.cpp")
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)





# cmake_minimum_required(VERSION 3.5)
# project(PantryPro C CXX)
# set(CMAKE_OSX_ARCHITECTURES x86_64)

# # MySQL paths
# set(MYSQLCPPCON_INCLUDE_DIR "mysql-connector-c++-8.1.0/include")
# set(MYSQLCPPCON_LIB_DIR "mysql-connector-c++-8.1.0/lib64")

# # Include header files
# include_directories(${MYSQLCPPCON_INCLUDE_DIR})

# # Link library directories
# link_directories(${MYSQLCPPCON_LIB_DIR})

# # Print results for debugging
# message(STATUS "MYSQLCPPCON_INCLUDE_DIRS: ${MYSQLCPPCON_INCLUDE_DIR}")
# message(STATUS "MYSQLCPPCON_LIBRARIES: ${MYSQLCPPCON_LIB_DIR}")

# # Setting RPATH
# set(CMAKE_INSTALL_RPATH "${MYSQLCPPCON_LIB_DIR}")
# set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# include(cmake/App.cmake)

# set(SOURCES "src/MyApp.h"
#             "src/MyApp.cpp"
#             "src/databaseConnection.h"
#             "src/recipeDatabase.h"
#             "src/recipe.h"
#             "src/recipeDatabase.cpp"
#             "src/databaseConnection.cpp"
#             "src/recipe.cpp"
#             "src/main.cpp")

# add_app("${SOURCES}")

# set(MYSQLCPPCONN_LIBRARY "libmysqlcppconn.9.dylib")
# set(SSL_LIB "libssl.3.dylib")

# target_link_libraries(PantryPro ${MYSQLCPPCONN_LIBRARY} ${SSL_LIB})

# Include(FetchContent)

# FetchContent_Declare(
#   Catch2
#   GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#   GIT_TAG        v3.0.1 # or a later release
# )

# FetchContent_MakeAvailable(Catch2)

# add_executable(tests "tests/test.cpp")
# target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
