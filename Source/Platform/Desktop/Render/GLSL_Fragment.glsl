#version 330 core

// Recieve the interpolated vertex attributes from the vertex shader
in vec3 vCol;

// Write out the fragment color to the framebuffer
out vec4 fragColor;

void main()
{
	fragColor = vec4(vCol.x, vCol.y, vCol.z, 1.0);
}