#/**********************************************************\
#
# Auto-generated CMakeLists.txt for the encrev2_plugin project
#
#\**********************************************************/

# Written to work with cmake 2.6
cmake_minimum_required (VERSION 2.6)
set (CMAKE_BACKWARDS_COMPATIBILITY 2.6)
set (CMAKE_BUILD_TYPE Debug)

add_definitions(-DPOSIX)

include(${CMAKE_DIR}/common.cmake)

set (PROJNAME ${PLUGIN_NAME})

#
# Dependencies detection
#
set(ENV{PKG_CONFIG_PATH} /usr/local/myvlc/lib/pkgconfig)
pkg_check_modules(VLC libvlc)

if (VLC_FOUND)
  message(STATUS "Found vlc. (libdir = ${VLC_LIBRARY_DIRS})")
else (VLC_FOUND)
  message(SEND_ERROR "libvlc not found, this is required. Maybe check the PKG_CONFIG_PATH variable")
endif (VLC_FOUND)

include_directories(${VLC_INCLUDE_DIRS})
link_directories(${VLC_LIBRARY_DIRS})


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
FIND_PACKAGE(Jingle)
include_directories(/usr/include)
include_directories(${JINGLE_INCLUDE_DIR})
include_directories(${EXPAT_INCLUDE_DIR})
include_directories(${SRTP_INCLUDE_DIR})
include_directories(${XMPPHELP_INCLUDE_DIR})


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

target_link_libraries(${PLUGIN_NAME} ${VLC_LIBRARIES} ${JINGLE_LIBRARIES})

install(TARGETS ${PLUGIN_NAME} LIBRARY DESTINATION ~/.mozilla/plugins)
