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

		# Add a custom target to copy the glsl shaders over to the executable
		# this is so they can be read in at runtime
		# See Concorde/Source/Platform/Desktop/Render/CMakeLists.txt
		if(GLSL_SHADERS_CACHE)
			# Add a custom command for each shader
			foreach(SHADER ${GLSL_SHADERS_CACHE})
				get_filename_component(SHADER_OUT ${SHADER} NAME)
				message("${SHADER_OUT}")
				target_sources(${concorde_target} PRIVATE ${SHADER_OUT})
				add_custom_command(POST_BUILD
					COMMAND "${CMAKE_COMMAND}" -E copy
					"${SHADER}"
					"${CMAKE_CURRENT_BINARY_DIR}/${SHADER_OUT}"
					DEPENDS "${SHADER}"
					OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${SHADER_OUT}"
					COMMENT "Copying shader ${SHADER_OUT} to ${concorde_target}")
			endforeach()
		else()
			message(FATAL_ERROR "Was not able to cache the glsl shaders?")
		endif()
	
	# We're targetting the Wii
	else()
		message("Adding Wii target ${concorde_target}.elf")
		add_executable("${concorde_target}.elf" "${concorde_sources}")

		# Get the absolute path of the outputs
		set(ELF_OUTPUT "${concorde_target}.elf")
		set(DOL_OUTPUT "${concorde_target}.dol")

		# Get that path to the devkit tool that produces dol files
		set(ELF2DOL "${DEVKITPRO}/tools/bin/elf2dol")
		if(WIN32 OR CONCORDE_WIN32)
			set(ELF2DOL "${ELF2DOL}.exe")
		endif()

		# Add a post build command to the concorde target which creates the dol file
		add_custom_command(TARGET "${concorde_target}.elf" POST_BUILD
			DEPENDS "${concorde_sources}"
			COMMAND "${ELF2DOL}" "${ELF_OUTPUT}" "${DOL_OUTPUT}"
			COMMENT "Producing dol file ..."
			)

		# Add a post build command to run the demo on dolphin
		add_custom_target("run_${concorde_target}"
			DEPENDS "${concorde_target}.elf"
			COMMAND "${CONC_DOLPHIN_CMD}" "-b" "${ELF_OUTPUT}"
			COMMENT "Running dolphin : ${CONC_DOLPHIN_CMD}"
			) 
		set_target_properties("run_${concorde_target}" PROPERTIES EXCLUDE_FROM_ALL TRUE)
		# So we can like to concorde regardles of if building for wii or desktop
		set(concorde_target "${concorde_target}.elf")
	endif()

	# link our new target to concorde
	target_link_libraries(${concorde_target} Concorde)
endfunction()