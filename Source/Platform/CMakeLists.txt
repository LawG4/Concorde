# Define which platform source the user is compiling for and then add the appropariate sources
if("${CACHE_PLATFORM}" STREQUAL "PLATFORM_WII")
	add_subdirectory(Wii)
else()
	add_subdirectory(Desktop)
endif()

# Add the translation layer headers
set(HEADERS
	ConcordePlatform.h)

# Add headers to target
target_sources(Concorde PRIVATE ${HEADERS})