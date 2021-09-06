# Add a compile def to allow the code base to know that we're on desktop
target_compile_definitions(Concorde PRIVATE CONCORDE_PLATFORM_DESKTOP)

# Find SDL2 using the user supplied config in project root
find_package(SDLCon)
target_link_libraries(Concorde PUBLIC "${SDLCON_LIBS}")
target_include_directories(Concorde PUBLIC "${SDLCON_INCLUDE}")

# Add all the source files
set(SOURCE 
	DesktopConcorde.c)

target_sources(Concorde PRIVATE ${SOURCE})