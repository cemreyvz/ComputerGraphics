#version 330 core

// Colors in RGBA
out vec4 FragColor;


// Input the color from the vertex shader
in vec3 color;
// Input the texture coordinates from the vertex shader
in vec2 texCoord;

// Getting the texture from the main function
uniform sampler2D tex0;


void main()
{
	FragColor = texture(tex0, texCoord);
}
