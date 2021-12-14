#shader vertex
#version 330 core

//Positions/Coordinates
layout(location = 0) in vec3 aPos;
// Colors
layout(location = 1) in vec3 aColor;


// Outputs the color for the Fragment Shader
out vec3 color;
// Controls the scale of the vertices
uniform float scale;


void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
}


#shader fragment
#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 color;


void main()
{
	FragColor = vec4(0.309, 0.592, 0.878, 1.0f);
}