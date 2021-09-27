cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
set(EXAMPLE_NAME 02_HelloTriangle)
project(${EXAMPLE_NAME} LANGUAGES NONE)



# Add the Concorde project
add_subdirectory(../../ ${CMAKE_CURRENT_BINARY_DIR}/Concorde)

# Make this project be the one that launches in VS studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${EXAMPLE_NAME})

# Add the executable
add_concorde_executable("${EXAMPLE_NAME}" "Main.c")