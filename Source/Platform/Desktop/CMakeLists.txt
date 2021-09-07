# Add a compile def to allow the code base to know that we're on desktop
target_compile_definitions(Concorde PRIVATE CONCORDE_PLATFORM_DESKTOP)

# Add all the source files
set(SOURCE 
	DesktopConcorde.c)

# Header files
set(HEADERS
	Desktop.h)

target_sources(Concorde PRIVATE ${SOURCE} ${HEADERS})



# Find SDL2, fallback to user config in root if SDL2.cmake is missing
find_package(SDL2)
if(NOT ${SDL2_INCLUDE_DIRS})
	message("Using Config.cmake in Concorde root dir to find SDL2")
	find_package(SDL2_Concorde)
endif()

target_link_libraries(Concorde PUBLIC "${SDL2_LIBS}")
target_include_directories(Concorde PUBLIC "${SDL2_INCLUDE_DIRS}")
