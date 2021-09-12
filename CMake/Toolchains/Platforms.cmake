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

# Set the platform string to lowercase so it's easier to compare
string(TOLOWER "${PLATFORM}" PLATFORM)


# Detect if the user wanted to deploy to the nintendo wii
string(FIND ${PLATFORM} "wii" PLATFORM_WII_SUBSTRING)
if(NOT ${PLATFORM_WII_SUBSTRING} EQUAL -1)
	# Detected wii
	message("Configuring build for Wii")
	set(PLATFORM "PLATFORM_WII")

	# Ensure that the user has passed a toolchain file variable or else the build won't work
	if(NOT CMAKE_TOOLCHAIN_FILE)
		message("Toolchain variable not set")
		message("In order for wii builds to work the toolchain file must be loaded early")
		message(FATAL_ERROR "use cmake -DCMAKE_TOOLCHAIN_FILE=<PATH TO CONCORDE>/Cmake/Toolchains/Wii.cmake ..")
	endif()


else()
	# Not detected wii, assume desktop
	message("Configuring build for Desktop")
	set(PLATFORM "PLATFORM_DESKTOP")

	# Include the desktop toolchain
endif()

# Cache the platform variable
set(CACHE_PLATFORM "${PLATFORM}" CACHE STRING "Concorde declaration storing the chosen target platform from command line options" FORCE)

# Set the languages to C and Cxx
enable_language(C CXX)