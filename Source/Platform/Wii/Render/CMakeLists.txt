cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

# Let concorde search for this directory for includes
target_include_directories(Concorde PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Rendering managing for Wii

# Add all the source files
set(SOURCE 
	GX_Render.c
	GX_Render_Immediate.c 
	GX_Render_Init.c
)

# Header files
set(HEADERS
	GX_Render.h
)

target_sources(Concorde PRIVATE ${SOURCE} ${HEADERS})