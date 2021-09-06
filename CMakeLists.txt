cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)
project(Concorde_PROJECT VERSION 0.1.0 LANGUAGES CXX C)

# Append custom cmake module finding directory
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMake/Modules/")

# Cache the command line option the user passed via -DPLATFORM=
if(PLATFORM)
	message("User defined the platfrom as: ${PLATFORM}")
else()
	message("You didn't pass a platform, assuming a desktop")
	set(PLATFORM "PLATFORM_DESKTOP")
endif()

if("${PLATFORM}" STREQUAL "PLATFORM_DESKTOP" OR "${PLATFORM}" STREQUAL "PLATFORM_WII")
	set(CACHE_PLATFORM ${PLATFORM} CACHE STRING "Sets if to build for wii or desktop")
else()
	message(FATAL_ERROR "Undefined platform ${PLATFORM}, please use -DPLATFORM=<PLATFORM_DESKTOP/PLATFORM_WII>")
endif()

# Create a target to put all the sources into
add_library(Concorde STATIC Source/Concore.c)

# Get all the source files 
add_subdirectory(Source)