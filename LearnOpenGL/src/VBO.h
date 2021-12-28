#pragma once
#include <glad/glad.h>
#include "Vertex.h"
class VBO
{
public:
	GLuint ID;
	VBO(Vertex vertices[], GLsizeiptr size );
	~VBO() { Delete(); };
	void Bind();
	void Unbind();
	void Delete();   
};