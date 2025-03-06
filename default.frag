#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Imports the color from the Vertex Shader
in vec4 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the current position from the Vertex Shader
in vec3 crntPos;

// Gets the Texture Unit from the main function
uniform sampler2D diffuse0;
uniform sampler2D specular0;
// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;

vec4 pointLight(){

	float ambient = 0.20f;

	vec3 lightVec = lightPos - crntPos;

	float dist = length(lightVec);
	
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);

	float a = 3.0;
	float b = 0.7;
	float intensity = 1.0f / (a * dist * dist + b * dist + 1.0f);
	//vektorprodukt
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	return texture(diffuse0, texCoord) * lightColor * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * lightColor * specular;
}

vec4 directionalLight(){

	float ambient = 0.75f;

	vec3 lightVec = lightPos - crntPos;

	float dist = length(lightVec);
	
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(0.4f, 1.0f, 0.1f));
	//vektorprodukt
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;
	vec4 realcolor = texture(diffuse0, texCoord);

	vec3 texcol = realcolor.rgb * lightColor.rgb * (diffuse + ambient) + texture(specular0, texCoord).r * lightColor.rgb * specular;
	return vec4(texcol, color.a);
	//return texture(diffuse0, texCoord);
	//return texture(diffuse0, texCoord) * lightColor * (diffuse + ambient) + texture(specular0, texCoord).r * lightColor * specular;
	//return texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * lightColor * specular;
	//return texture(diffuse0, texCoord) * lightColor * (diffuse + ambient);
	//return texture(diffuse0, texCoord);
}

vec4 spotLight()
{
	// controls how big the area that is lit up is
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	vec3 coneDirection = normalize(vec3(0.0f, 0.0f, -1.0f));
	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	// calculates the intensity of the crntPos based on its angle to the center of the light cone
	float angle = dot(coneDirection, -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;

}

vec4 noTex(){
	float ambient = 1.0f;
	
	vec3 lightVec = lightPos - crntPos;

	float dist = length(lightVec);
	
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(0.4f, 1.0f, 0.0f));
	//vektorprodukt
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	return  color * (diffuse + ambient);

}

void main()
{

	FragColor = directionalLight();

}