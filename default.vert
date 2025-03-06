#version 330 core
//Coordinates
layout (location = 0) in vec3 aPos;

//normal
layout (location = 1) in vec3 aNormal;

//Colors
layout (location = 2) in vec4 aColor;
//texture
layout (location = 3) in vec2 aTex;


out vec4 color;

out vec2 texCoord;

out vec3 Normal;

out vec3 crntPos;

uniform mat4 camMatrix;

uniform mat4 model;
uniform mat3 normalMatrix; 

void main()
{
	crntPos = vec3(model * vec4(aPos, 1.0f));
	// Assigns the normal from the Vertex Data to "Normal"
	Normal = normalize(normalMatrix * aNormal);
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;
	
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0);
}