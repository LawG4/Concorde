# Find SDL2 using the user supplied config in project root
find_package(SDLCon)
target_link_libraries(Concorde PRIVATE SDLCON_LIBS)
target_include_directories(Concorde PRIVATE SLDCON_INCLUDE)