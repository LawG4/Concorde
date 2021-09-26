cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

Set (Source
	)

set(Headers
	ConcordeInternal.h)

target_sources(Concorde PRIVATE ${Headers} ${Source})
target_include_directories(Concorde PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Add in the platform specific code base with abstraction layer
add_subdirectory(Platform)

# Add in the common code for the input system
add_subdirectory(Input)

# Add in the common code for rendering. That will be tracking 
# the state and also ensuring that enough vertices have been
# submitted so that GX doesn't hang
add_subdirectory(Render)  