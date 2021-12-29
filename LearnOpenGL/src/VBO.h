#pragma once
#include <glad/glad.h>
#include "Vertex.h"
class VBO
{
public:
	GLuint ID;
	VBO(GLfloat vertices[], GLsizeiptr size );
	~VBO() { Delete(); };
	void Bind();
	void Unbind();
	void Delete();   
};