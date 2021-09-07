# Find SDL using the user supplied config without conflicting with their findSDL2 cmake
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

include("${PROJECT_SOURCE_DIR}/Config.cmake")

set(SDLCON_INCLUDE "${SDL_PATH}/include")
set(SDLCON_LIB_DIR "${SDL_PATH}/lib/${CONC_HOST_ARCH}")

# Check if the directories exist
if(NOT EXISTS ${SDLCON_INCLUDE})
	message(FATAL_ERROR "Check config. SDL2 include directory not found : ${SDLCON_INCLUDE}")
endif()
if(NOT EXISTS ${SDLCON_LIB_DIR})
	message(FATAL_ERROR "Check config. SDL2 include Lib not found : ${SDLCON_LIB_DIR}")
endif()

# Pass variables that a normal find SDL2 file would back to the calling file
set(SDL2_LIBS "${SDLCON_LIB_DIR}/SDL2.lib" "${SDLCON_LIB_DIR}/SDL2main.lib")
set(SDL2_INCLUDE_DIRS "${SDLCON_INCLUDE}")