cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

# Link to the Wii libraries
target_link_libraries(Concorde wiiuse bte ogc m)

# Let wii code include these headers
target_include_directories(Concorde PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Add all the source files
set(SOURCE 
	WiiConcorde.c
	WiiInputs.c)

# Header files
set(HEADERS
	Wii.h)

target_sources(Concorde PRIVATE ${SOURCE} ${HEADERS})

# Add the render subdirectory
add_subdirectory(Render)