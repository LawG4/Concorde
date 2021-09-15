# Link to the Wii libraries
target_link_libraries(Concorde wiiuse bte ogc m)

# Add all the source files
set(SOURCE 
	WiiConcorde.c)

target_sources(Concorde PRIVATE ${SOURCE})