cmake_minimum_required(VERSION 2.8.7)
enable_testing()
add_definitions(-std=c++11)
include(CheckIncludeFileCXX)
#include(CheckFunctionExists)
include(CheckLibraryExists)
project(rumpeltree++ CXX)
set(prefix      ${CMAKE_INSTALL_PREFIX})
set(exec_prefix ${CMAKE_INSTALL_PREFIX})
set(libdir      ${CMAKE_INSTALL_PREFIX}/lib)
set(includedir  ${CMAKE_INSTALL_PREFIX}/include)
set(CMAKE_CXX_FLAGS                "-Wall -O3 -std=c++0x -Werror -Wctor-dtor-privacy -Wuninitialized -Winit-self -Wmissing-include-dirs -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -Wold-style-cast -Weffc++")
CHECK_INCLUDE_FILE_CXX(cryptopp/hmac.h CRYPTOPP_HMAC_INCLUDE)
CHECK_INCLUDE_FILE_CXX(cryptopp/sha.h CRYPTOPP_SHA_INCLUDE)
CHECK_INCLUDE_FILE_CXX(cryptopp/osrng.h CRYPTOPP_OSRNG_INCLUDE)
IF(CRYPTOPP_HMAC_INCLUDE)
ELSE(CRYPTOPP_HMAC_INCLUDE)
    MESSAGE(FATAL_ERROR "No cryptopp/hmac.h header found")
ENDIF(CRYPTOPP_HMAC_INCLUDE)
IF(CRYPTOPP_SHA_INCLUDE)
ELSE(CRYPTOPP_SHA_INCLUDE)
    MESSAGE(FATAL_ERROR "No cryptopp/sha.h header found")
ENDIF(CRYPTOPP_SHA_INCLUDE)
IF(CRYPTOPP_OSRNG_INCLUDE)
ELSE(CRYPTOPP_OSRNG_INCLUDE)
    MESSAGE(FATAL_ERROR "No cryptopp/osrng.h header found")
ENDIF(CRYPTOPP_OSRNG_INCLUDE)
set(rumpeltree++_SOURCES
        Client.cpp
        ConcreteClient.cpp
        ConcreteNode.cpp
        ConcreteServer.cpp
        ConcreteStorage.cpp
        Node.cpp
        Server.cpp
        Storage.cpp
        base32.cpp
        rumpelstiltskin.cpp
	string.cpp)
add_library(rumpeltree++ SHARED ${rumpeltree++_SOURCES})
SET_TARGET_PROPERTIES(rumpeltree++ PROPERTIES VERSION 0.1.1 SOVERSION 2)
target_link_libraries(rumpeltree++ crypto++)
install_targets(/lib rumpeltree++)
install(FILES rumpelstiltskin.hpp DESTINATION include)
add_executable(randomsecrettest test_random_secret.cpp)
target_link_libraries(randomsecrettest rumpeltree++)
add_test(tests.randomsecret randomsecrettest)
add_executable(storagepath1test test_storage_path1.cpp)
target_link_libraries(storagepath1test rumpeltree++)
add_test(tests.storagepath1 storagepath1test)
add_executable(demo test.cpp)
target_link_libraries(demo rumpeltree++)

