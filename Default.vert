#version 330 core

// Positions and Coordinates
layout (location = 0) in vec3 aPos;

// Colors
layout (location = 1) in vec3 aColor;

// Texture Coordinates
layout (location = 2) in vec2 aTex;


// Output the color for the Fragment Shader
out vec3 color;

// Texture coordinates to the fragment shader
out vec2 texCoord;

// Import the camera matrix from the main function
uniform mat4 camMatrix;


void main()
{
	// Output the positions of all vertices
	gl_Position = camMatrix * vec4(aPos, 1.0);

	// Assign the colors from the Vertex Data 
	color = aColor;

	// Assigns the texture coordinates from the vertex data 
	texCoord = aTex;
}