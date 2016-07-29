cmake_minimum_required(VERSION 2.6)
project(Chip8Emu)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_SOURCE_DIR}/cmake
)

set(LANGUAGE "CXX")

# Clang / C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

# Dependencies

# SDL2 Libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

#set(BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
#set(CONF_DIR ${CMAKE_INSTALL_PREFIX}/etc)
#set(LIBS_DIR ${CMAKE_INSTALL_PREFIX}/lib)

# For Unix systems set the rpath so that libraries are found
set(CMAKE_INSTALL_RPATH ${LIBS_DIR})
set(CMAKE_INSTALL_NAME_DIR ${LIBS_DIR})

# Run out of build tree
set(CMAKE_BUILD_WITH_INSTALL_RPATH OFF)

# Project info
set(chip8_EXEC chip8-emu)
#set(framework_LIB framework)

#set(FRAMEWORK_SRC_DIR ${CMAKE_SOURCE_DIR}/src/framework)

# Source Tree
add_subdirectory(src)
