cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

# Let other desktop concorde files include this subdirectory
target_include_directories(Concorde PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# build up the list of render files 
set(GL_RENDER_HEADER
	GL_Render.h
)

set(GL_RENDER_SOURCE
	GL_Debug.c
	GL_Render_init.c
	GL_Render_Immediate.c
)

# Add the render source to concorde
target_sources(Concorde PRIVATE ${GL_RENDER_HEADER} ${GL_RENDER_SOURCE})

# Add the shaders to the build system
set(GLSL_SHADERS
	GLSL_Vertex.glsl 
	GLSL_Fragment.glsl
)
target_sources(Concorde PRIVATE ${GLSL_SHADERS})

# We need to cache the file path of the GLSL shaders
# That way we can make a custom command for each executable
# to copy the shaders from the source to the build dir
# See Concorde/CMake/Toolchains/AddExecutable.cmake

set(GLSL_SHADERS_CACHE "")
foreach(SHADER ${GLSL_SHADERS})
	list(APPEND GLSL_SHADERS_CACHE "${CMAKE_CURRENT_LIST_DIR}/${SHADER}")
endforeach()
set(GLSL_SHADERS_CACHE "${GLSL_SHADERS_CACHE}" CACHE STRING "File path to all the glsl shaders in the source tree" FORCE)

