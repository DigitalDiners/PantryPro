cmake_minimum_required(VERSION 3.5)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

project(PantryPro C CXX)

##################################################################
# Depending on the Operating System, 
# we set the MYSQL variables to different directories
if(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Darwin")
    message("Setting libraries for operating system: MacOS")

    set(CMAKE_OSX_ARCHITECTURES x86_64)#REQUIRED FOR MAC OSX

    # MySQL paths using the CMAKE_CURRENT_SOURCE_DIR variable
    set(MYSQLCPPCON_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/mysql-connector-c++-8.1.0/include")
    set(MYSQLCPPCON_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/mysql-connector-c++-8.1.0/lib64")

    # Include header files
    include_directories(${MYSQLCPPCON_INCLUDE_DIR})

    # Full paths for macOS libraries
    set(MYSQLCPPCONN_LIBRARY "${MYSQLCPPCON_LIB_DIR}/libmysqlcppconn.9.dylib")
    set(SSL_LIB "${MYSQLCPPCON_LIB_DIR}/libssl.3.dylib")

    set(CRYPTO_LIB "${MYSQLCPPCON_LIB_DIR}/libcrypto.3.dylib")
endif()
if(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
    message("Setting libraries for operating system: Windows")

    # MySQL paths using the CMAKE_CURRENT_SOURCE_DIR variable
    set(MYSQLCPPCON_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/mysql-connector-c++-8.1.0-winx64/include")
    set(MYSQLCPPCON_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/mysql-connector-c++-8.1.0-winx64/lib64/vs14")

    # Include header files
    include_directories(${MYSQLCPPCON_INCLUDE_DIR})

    # Paths to Windows libraries
    set(MYSQLCPPCONN_LIBRARY "${MYSQLCPPCON_LIB_DIR}/mysqlcppconn.lib")
    set(SSL_LIB "${MYSQLCPPCON_LIB_DIR}/libssl.lib")

    set(CRYPTO_LIB "${MYSQLCPPCON_LIB_DIR}/libcrypto.lib")

endif()#Darwin or Windows

######################################################################


# Option for enabling building of tests
option(BUILD_TESTING "Builds test executable." OFF) 


# Set the base directory based on the current source directory
set(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include(cmake/App.cmake)

set(SOURCES "src/MyApp.h"
            "src/MyApp.cpp"
            "src/databaseConnection.h"
            "src/recipeDatabase.h"
            "src/recipe.h"
            "src/recipeImage.h"
            "src/recipeImage.cpp"
            "src/recipeDatabase.cpp"
            "src/databaseConnection.cpp"
            "src/recipe.cpp"
            "src/main.cpp")

add_app("${SOURCES}")

# Setting RPATH
set_target_properties(PantryPro PROPERTIES
    INSTALL_RPATH "@executable_path"
)

#link libs to the executable target
target_link_libraries(PantryPro ${MYSQLCPPCONN_LIBRARY} ${SSL_LIB})

#Add libs to the executable directory
set(DYLIBS ${MYSQLCPPCONN_LIBRARY} ${SSL_LIB} ${CRYPTO_LIB})
foreach(dylib ${DYLIBS})
    add_custom_command(
        TARGET PantryPro POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${dylib}
        $<TARGET_FILE_DIR:PantryPro>
    )
endforeach()

if(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Darwin")
    # Adjusting library paths inside the dylibs for macOS
    add_custom_command(TARGET PantryPro POST_BUILD
        COMMAND install_name_tool -change "libcrypto.3.dylib" "@executable_path/libcrypto.3.dylib" $<TARGET_FILE_DIR:PantryPro>/libssl.3.dylib
        COMMAND install_name_tool -change "libcrypto.3.dylib" "@executable_path/libcrypto.3.dylib" $<TARGET_FILE_DIR:PantryPro>/libmysqlcppconn.9.dylib
        COMMAND install_name_tool -change "libssl.3.dylib" "@executable_path/libssl.3.dylib" $<TARGET_FILE_DIR:PantryPro>/libmysqlcppconn.9.dylib
    )

elseif(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
    # Adding all needed dll files to the executable directory
    set(MYSQLCPPCON_DLL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/mysql-connector-c++-8.1.0-winx64/lib64")
    set(MYSQLCPPCONN_DLL "${MYSQLCPPCON_DLL_DIR}/mysqlcppconn-9-vs14.dll")
    set(SSL_DLL "${MYSQLCPPCON_DLL_DIR}/libssl-3-x64.dll")
    set(CRYPTO_DLL "${MYSQLCPPCON_DLL_DIR}/libcrypto-3-x64.dll")

    set(MYSQL_DLLS ${MYSQLCPPCONN_DLL} ${SSL_DLL} ${CRYPTO_DLL})
    
    foreach(mysql_dll ${MYSQL_DLLS})
        add_custom_command(
            TARGET PantryPro POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${mysql_dll}
            $<TARGET_FILE_DIR:PantryPro>
        )
    endforeach()
endif()# MacOs or Windows

##################################################################################
# Build Testing below
##################################################################################

if(BUILD_TESTING)
  include(FetchContent)

  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.0.1 # or a later release
  )

  FetchContent_MakeAvailable(Catch2)

  add_executable(tests "tests/test.cpp")
  add_executable(UnitTests "tests/recipeTests.cpp")

  target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
  target_link_libraries(UnitTests PRIVATE Catch2::Catch2WithMain)
endif()