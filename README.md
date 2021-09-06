# ***Project Concorde***

------

There's no line by line debugging available for coding on the Wii, logging is difficult as you have to retrieve it physically from the wii, or mount a virtual drive image from the emulator. The aim of this project is to allow you line by line debugging on your desktop and then port the code easily to the Wii. 

When you're coding on the Wii, a lot of the time it's easiest to embed the assets inside the binary. This will be the approach for this project.

## Structure

 The project is split into three different parts:

- **Platform specific code**. Managing rendering, windowing and input event signalling
- **Translation layer**. Code that will be available to the user. Responding to inputs and requesting a model be rendered
- **Asset Processing**. Prepping assets for packing into the binary executable 