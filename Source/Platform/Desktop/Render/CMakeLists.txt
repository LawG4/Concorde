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