#version 330 core

// Recieve vertex attributes from the CPU
in vec3 aPos;
in vec3 aCol;

// Pass the required attributes onto fragment shader
out vec3 vCol;

//Enter into the main function 
void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

	// Pass on the variables
	vCol = aCol;
}