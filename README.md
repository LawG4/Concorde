# ***Project Concorde***

------

There's no line by line debugging available for coding on the Wii, logging is difficult as you have to retrieve it physically from the wii, or mount a virtual drive image from the emulator. The aim of this project is to allow you access line by line debugging on your desktop and then port the code easily to the Wii. 

## Quick Start

### Dependencies 

Things to make sure you download before you get going:

- Cmake 3.13 or greater
- Ninja build tool
- DevkitPro for Wii

### Create a CMake Project for your build

Start by declaring a project with no languages, this prevents early compiler checks from failing

```cmake
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
set(PROJ_NAME ExampleProject)
project(${PROJ_NAME} LANGUAGES NONE)
```

Add the Concorde directory as a CMake subdirectory. Specify the source directory, since it is out of your source tree

```cmake
add_subdirectory(<PATH_TO_CONCORDE_ROOT_DIRECTORY> ${CMAKE_BINARY_DIR}/Concorde)
```

Create a list of source files 

```cmake
set(SOURCE_FILES Main.c SecondFile.h SecondFile.c)
```

Add an executable using a function supplied by Concorde. Since the second argument is a list, it must be in quotes

```cmake
add_concorde_executable("${PROJ_NAME}" "${SOURCE_FILES}")
```

### Configure your build

- You can start your development on Desktop and start writing your project on there

  ```bash
  # Starting from your projects root directory
  mkdir build_desktop
  cd build_desktop
  cmake ..
  ```

- When you have finished developing on desktop, configure a build for Wii. 
  Unfortunately for windows users; Windows sucks. Using visual studio generator doesn't allow for custom compilers, and even when you use ninja the compiler seemingly fails CMake's checks, despite not returning an error. So you'll need to do this build on WSL. Thankfully you'll only be calling the build, so it'll be nice and quick.

  ```bash
  # Starting from your projects root directory
  mkdir build_wii
  cd build_wii
  cmake -DCMAKE_TOOLCHAIN_FILE=CMake/Toolchains/Wii.cmake -GNinja ..
  # Actually build
  cmake --build .
  ```

## Structure

 The project is split into three different parts:

- **Platform specific code**. Managing rendering, windowing and input event signalling
- **Translation layer**. Code that will be available to the user. Responding to inputs and requesting a model be rendered
- **Asset Processing**. Prepping assets for packing into the binary executable 