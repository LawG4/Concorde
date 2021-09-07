# Find SDL using the user supplied config without conflicting with their findGLEW cmake
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

include("${PROJECT_SOURCE_DIR}/Config.cmake")

# if the user has windows and x32 then path changes to win32 for libs
if(WIN32 AND "${CONC_HOST_ARCH}" STREQUAL "x32")
	set(GLEW_ARCH "Win32")
else()
	set(GLEW_ARCH "${CONC_HOST_ARCH}")
endif()

set(GLEW_INCLUDE_DIRS "${GLEW_PATH}/include")
set(GLEW_LIB_DIR "${GLEW_PATH}/lib/Release/${GLEW_ARCH}")

# Now check that these directories are valid
if(NOT EXISTS "${GLEW_INCLUDE_DIRS}")
	message(FATAL_ERROR "GLEW include directory not valid : ${GLEW_INCLUDE_DIRS}")
endif()
if(NOT EXISTS "${GLEW_LIB_DIR}")
	message(FATAL_ERROR "GLEW lib directory not valid : ${GLEW_LIB_DIR}")
endif()

# Set the libs depending on operating system
if(WIN32)
	set(GLEW_LIBRARIES "${GLEW_LIB_DIR}/glew32.lib")
else()
	set(GLEW_LIBRARIES "${GLEW_LIB_DIR}/libGLEW.so")
endif()