cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)
project(Concorde LANGUAGES NONE)

# Avoids Concorde being added multiple times
if(TARGET Concorde)
	return()
endif()

# Append custom cmake module finding directory
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMake/Modules/")

# Detect the users platform selection
include("${PROJECT_SOURCE_DIR}/CMake/Toolchains/Platforms.cmake")

# Add the concorde include directories to Concorde and projects including Concorde
include_directories("${PROJECT_SOURCE_DIR}/Include")

# Create a target to put all the sources into
add_library(Concorde STATIC Source/Concore.c Include/Concorde.h)

# Get the rest of the Concorde source files 
add_subdirectory(Source)

# Add the examples to the build system
add_subdirectory(Examples)

# Sort the source files to have the same folder structure
get_target_property(SourceList Concorde SOURCES)
function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)
assign_source_group(${SourceList})
