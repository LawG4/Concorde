cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

# Add this folder to the list of folders that sources inside of concorde can access
# This is so we don't have to waste stack space by using a set render mode etc
target_include_directories(Concorde PRIVATE "${CMAKE_CURRENT_LIST_DIR}")

set(HEADERS
	Concorde_Internal_Render.h
)

set(SOURCES
	Render.c
)

target_sources(Concorde PRIVATE ${HEADERS} ${SOURCES})