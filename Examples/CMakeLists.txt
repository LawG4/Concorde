cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(Concorde_Examples
	01_HelloConcorde)

foreach(example ${Concorde_Examples})
	add_subdirectory(${example})
endforeach()