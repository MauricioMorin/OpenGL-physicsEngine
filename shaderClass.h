#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include<glm/glm.hpp>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint ID;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);


	void setBool(const char* uniform, bool value);
	void setInt(const char* uniform, int value);
	void setFloat(const char* uniform, float value);
	void setVec3(const char* uniform, glm::vec3 value);
	// Activates the Shader Program
	void Activate();
	// Deletes the Shader Program
	void Delete();

	
};
#endif