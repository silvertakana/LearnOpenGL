#pragma once
#include <glad/glad.h>
#include <vector>

class EBO
{
public:
	GLuint ID;
	EBO(std::vector<GLuint>& indices);
	~EBO() { Delete(); };
	void Bind();
	void Unbind();
	void Delete();
};