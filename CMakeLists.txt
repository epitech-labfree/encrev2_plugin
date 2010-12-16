#/**********************************************************\
#
# Auto-generated CMakeLists.txt for the encrev2_plugin project
#
#\**********************************************************/

# Written to work with cmake 2.6
cmake_minimum_required (VERSION 2.6)
set (CMAKE_BACKWARDS_COMPATIBILITY 2.6)

include(${CMAKE_DIR}/common.cmake)

set (PROJNAME ${PLUGIN_NAME})

#
# Dependencies detection
#
set(ENV{PKG_CONFIG_PATH} /usr/local/myvlc/lib/pkgconfig)
find_package(PkgConfig REQUIRED)
pkg_check_modules(VLC libvlc)

if (VLC_FOUND)
  message(STATUS "Found vlc. (libdir = ${VLC_LIBRARY_DIRS})")
else (VLC_FOUND)
  message(SEND_ERROR "libvlc not found, this is required. Maybe check the PKG_CONFIG_PATH variable")
endif (VLC_FOUND)

include_directories(${VLC_INCLUDE_DIRS})
link_directories(${VLC_LIBRARY_DIRS})

browserplugin_project(${PROJNAME})

file (GLOB GENERAL RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    [^.]*.cpp
    [^.]*.h
    [^.]*.cmake
    )

# Generated files are stored in ${GENERATED} by the project configuration
SET_SOURCE_FILES_PROPERTIES(
    ${GENERATED}
    PROPERTIES
        GENERATED 1
    )

SOURCE_GROUP(Generated FILES
    ${GENERATED}
    )

SET( SOURCES
    ${GENERAL}
    ${GENERATED}
    )

# This will include Win/projectDef.cmake, Linux/projectDef.cmake, etc
include_platform()

target_link_libraries(${PLUGIN_NAME} ${VLC_LIBRARIES})


