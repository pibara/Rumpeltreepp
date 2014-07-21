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
# Initialize CXXFLAGS.
SET(CMAKE_CXX_COMPILER             "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS                "-Wall -O3 -std=c++0x -Werror -Weffc++ -Wold-style-cast -Wctor-dtor-privacy -Wuninitialized -Winit-self -Wmissing-include-dirs -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code")
SET (CMAKE_AR      "/usr/bin/llvm-ar-3.4")
SET (CMAKE_LINKER  "/usr/bin/llvm-ld-3.4")
SET (CMAKE_NM      "/usr/bin/llvm-nm-3.4")
SET (CMAKE_OBJDUMP "/usr/bin/llvm-objdump-3.4")
SET (CMAKE_RANLIB  "/usr/bin/llvm-ranlib-3.4")
ADD_DEFINITIONS(-D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE)
#Check for openssl lib and headers.
#FIND_PACKAGE(Crypto++ REQUIRED)
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
        rumpelstiltskin.cpp)
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

