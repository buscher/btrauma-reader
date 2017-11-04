project(btrauma-reader)
cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

include(CheckCXX11Features)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_COMPILER_FLAGS}")

find_package(Qt5 REQUIRED COMPONENTS Widgets Core Xml Qml Quick)

set(btrauma_game_SRCS
    game/blevel.cpp
    game/bframe.cpp
    game/bframeexit.cpp
    game/bframevideo.cpp
    game/bframealtmirror.cpp

    game/bsoundgroup.cpp
    game/bsoundcomment.cpp
    game/bcommentonvisit.cpp
    game/bcommentontrigger.cpp

    game/btraumareader.cpp
    game/bcoverprovider.cpp
)

set(btrauma_platform_SRCS
    platform/bfilemanager.cpp

    platform/btraumaquickview.cpp
    platform/btraumagameconfig.cpp
    platform/btraumalevelconfig.cpp
    platform/bgamemanager.cpp
)

set(btrauma-reader_SRCS
    ${btrauma_game_SRCS}
    ${btrauma_platform_SRCS}

    main.cpp
)

add_executable(btrauma-reader ${btrauma-reader_SRCS})

qt5_use_modules(btrauma-reader Widgets Core Xml Qml Quick)

add_definitions(-DQT_NO_CAST_FROM_ASCII -DQT_STRICT_ITERATORS)
add_definitions(-DQT_USE_FAST_OPERATOR_PLUS)
add_definitions(-DQT_USE_QSTRINGBUILDER)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -pedantic")

configure_file (
  "${PROJECT_SOURCE_DIR}/btraumaconfig.h.in"
  "${PROJECT_BINARY_DIR}/btraumaconfig.h"
)

install(TARGETS btrauma-reader RUNTIME DESTINATION bin)
