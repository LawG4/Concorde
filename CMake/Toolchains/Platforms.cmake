# The point of this file is determine which toolchain the user wants to use
# And then call to it
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

# Read the command line option -DPLATFORM=
if(PLATFORM)
	message("User defined the platfrom as: ${PLATFORM}")
else()
	message("User didn't pass a platform, assuming they are deploying for desktop")
	set(PLATFORM "PLATFORM_DESKTOP")
endif()

if("${PLATFORM}" STREQUAL "PLATFORM_DESKTOP" OR "${PLATFORM}" STREQUAL "PLATFORM_WII")
	set(CACHE_PLATFORM ${PLATFORM} CACHE STRING "Sets if to build for wii or desktop" FORCE)
else()
	message(FATAL_ERROR "Undefined platform ${PLATFORM}, please use -DPLATFORM=<PLATFORM_DESKTOP/PLATFORM_WII>")
endif()
