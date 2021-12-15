#pragma once
#include <glad/glad.h>
#include <string>
class Shader
{
public:
	GLuint  ID;
	Shader(const char* shaderFilePath);
	Shader(std::string shaderFilePath);
	Shader(const char* vertexFilePath,const char* fragmentFilePath);
	Shader(std::string vertexFilePath, std::string fragmentFilePath);
	~Shader();
	void Activate();
	void Delete();
private:
	void Create(const char* vertexShaderSource, const char* fragmentShaderSource);
	void compileErrors(unsigned int shader, const char* type);
};