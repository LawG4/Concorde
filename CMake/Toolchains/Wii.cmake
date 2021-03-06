cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
# Make Cmake create a Wii compatable build system
# The toolchain needs to be passed during the configuration step at command line
# So we know the user is building for wii, set the internal cmake variable to use wii
set(PLATFORM "PLATFORM_WII")
set(CACHE_PLATFORM "${PLATFORM}" CACHE STRING "Concorde declaration storing the chosen target platform from command line options" FORCE)

# Cmake does some compiling tests, now for some reason this fails because it can't find the toolchain file
# that's because we're using a local path for cmake
# so make the toolchain variable global
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/Wii.cmake")

# When we set cmake to cross compile, the win32 variable becomes unset 
# we need that variable because windows tools need .exe suffix to be considered valid
if(WIN32)
	set(CONCORDE_WIN32 TRUE)
	set(CONCORDE_WIN32 "${CONCORDE_WIN32}" CACHE BOOL "If the build machine is running windows natively")
endif()

# We need to ensure that Cmake doesn't look for the host system compilers and libraries 
# inorder to do that we need to set the appropariate cmake variables
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR "powerpc-eabi")
set(CMAKE_EXECUTABLE_FORMAT "ELF") 
set(CMAKE_CROSS_COMPILING ON)

# Make CMake test the compiler by compiling a library instead of an executable
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# Try To force CMake to think that the compilers works
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_FORCED True)
set(CMAKE_C_COMPILER_FORCED True)


# Find the path to the devkitpro pro install by first checking the environment variable
# However on windows that environment variable won't work. 
# So check if the environment variable has a folder at that location
# if not then use the config file supplied by the user.
set(DEVKITPRO $ENV{DEVKITPRO})
if(NOT EXISTS ${DEVKITPRO})
	include("${CMAKE_CURRENT_LIST_DIR}/../../Config.cmake")
endif()
if(NOT EXISTS ${DEVKITPRO})
	message(FATAL_ERROR "Could not find DevkitPro Path. Configure the Concorde Config.cmake")
endif()

# If we are on windows the compiler needs to have an exe extension
if(WIN32 OR CONCORDE_WIN32)
	set(TOOLS_SUFFIX ".exe")
else()
	set(TOOLS_SUFFIX "")
endif()

# Define the location prerequisite path to the devkitPPC tools
set(TOOLS_PREFIX "${DEVKITPRO}/devkitPPC/bin/powerpc-eabi-")
set(CMAKE_C_COMPILER "${TOOLS_PREFIX}gcc${TOOLS_SUFFIX}")
set(CMAKE_CXX_COMPILER "${TOOLS_PREFIX}g++${TOOLS_SUFFIX}")

# Set the basic compiler flags that make the compiler build for wii
set(CMAKE_C_FLAGS "-Wall -Wextra -DGEKKO -mrvl -mcpu=750 -meabi -mhard-float")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")

# Link to the default libraries
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -L${DEVKITPRO}/libogc/lib/wii")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lwiiuse -lbte -logc -lm")

# Pass the C flags to CXX
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")

# Set the basic include directories
include_directories("${DEVKITPRO}/libogc/include")

# Set the basic link directories
link_directories("${DEVKITPRO}/libogc/lib/wii")

# Finally use cmake to generate a compiler commands data base that can be used for intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS True)