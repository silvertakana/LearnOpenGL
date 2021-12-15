#include "shaderClass.h"
#include "handleFiles.h"
#include "handleShader.h"
#include <iostream>

Shader::Shader(const char* shaderFilePath)
{
	auto [vertex, fragment] = loadShader(shaderFilePath);
	Create(vertex.c_str(), fragment.c_str());
}

Shader::Shader(std::string shaderFilePath)
{
	auto [vertex, fragment] = loadShader(shaderFilePath.c_str());
	Create(vertex.c_str(), fragment.c_str());
}

Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath)
{
	Create(loadFile(vertexFilePath).c_str(), loadFile(fragmentFilePath).c_str());
}

Shader::Shader(std::string vertexFilePath, std::string fragmentFilePath)
{
	Create(loadFile(vertexFilePath.c_str()).c_str(), loadFile(fragmentFilePath.c_str()).c_str());
	 
}

Shader::~Shader()
{
	Delete();
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::Create(const char* vertexShaderSource, const char* fragmentShaderSource )
{

	ID = glCreateProgram();//the shader program
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);//the vertex shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//the fragment shader
		//putting the shader source into the shader
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		//compile the shader
		glCompileShader(vertexShader);
		compileErrors(vertexShader, "VERTEX");
		glCompileShader(fragmentShader);
		compileErrors(vertexShader, "FRAGMENT");

		//attach the shader to the program
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		//link the program with openGL
		glLinkProgram(ID);
		compileErrors(ID, "PROGRAM");

		//delete the unuse shader
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}
