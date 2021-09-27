# Add a compile def to allow the code base to know that we're on desktop
target_compile_definitions(Concorde PRIVATE CONCORDE_PLATFORM_DESKTOP)

# Add all the source files
set(SOURCE 
	DesktopConcorde.c)

# Header files
set(HEADERS
	Desktop.h)

target_sources(Concorde PRIVATE ${SOURCE} ${HEADERS})

# Add in the rendering subdirectory
add_subdirectory(Render)

# Find OpenGL
find_package(OpenGL REQUIRED QUIET)
target_link_libraries(Concorde PUBLIC ${OPENGL_LIBRARIES})
target_include_directories(Concorde PUBLIC ${OPENGL_INCLUDE_DIRS})

# Find SDL2, fallback to user config in root if SDL2.cmake is missing
find_package(SDL2 QUIET)
if(NOT ${SDL2_FOUND})
	message("SDL2 : Using Config.cmake in Concorde root dir to find SDL2")
	find_package(SDL2_Concorde)
endif()

target_link_libraries(Concorde PUBLIC "${SDL2_LIBS}")
target_include_directories(Concorde PUBLIC "${SDL2_INCLUDE_DIRS}")

# Find GLEW 
set(GLEW_USE_STATIC_LIBS true)
find_package(GLEW QUIET)
if(NOT ${GLEW_INCLUDE_DIRS})
	message("GLEW : Using Config.cmake in Concorde root dir to find GLEW")
	find_package(GLEW_Concorde)
endif()
target_link_libraries(Concorde PUBLIC ${GLEW_LIBRARIES})
target_include_directories(Concorde PUBLIC ${GLEW_INCLUDE_DIRS})