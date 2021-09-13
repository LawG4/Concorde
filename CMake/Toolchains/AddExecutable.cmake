# This file aims to add a function that will add an executable to a target 
# The executable required changes based on the target platform
# On Wii we need an ELF and a DOL
# on desktop we only need a regular platform
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

function(add_concorde_executable concorde_target concorde_sources)
	# Ensure that we have a platform to target
	if(NOT CACHE_PLATFORM)
		message(FATAL_ERROR "Platform hasn't been declared, so we can't target a platform")
	endif()

	# If we're on desktop we only need to add one target
	if(NOT "${CACHE_PLATFORM}" STREQUAL "PLATFORM_WII")
		message("Adding Desktop target ${concorde_target}")
		add_executable(${concorde_target} "${concorde_sources}")
	
	# We're targetting the Wii
	else()
		set(concorde_target "${concorde_target}.elf")
		message("Adding Wii target ${concorde_target}")
		add_executable(${concorde_target} "${concorde_sources}")

		# Add a custom target for the DOL file
	endif()

	# link our new target to concorde
	target_link_libraries(${concorde_target} Concorde)
endfunction()