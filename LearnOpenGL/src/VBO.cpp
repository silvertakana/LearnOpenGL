#include "VBO.h"

VBO::VBO(GLfloat verticies[], GLsizeiptr size)
{
	glGenBuffers(1, &ID);
}

void VBO::Bind()
{}

void VBO::Unbind()
{}

void VBO::Delete()
{}
