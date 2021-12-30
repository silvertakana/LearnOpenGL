#pragma once

#include <string>
#include <vector>

#include "VAO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"

class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures; 

	VAO VAO;

	Mesh(std::vector <Vertex> i_verticies, std::vector <GLuint> i_indices, std::vector <Texture> i_textures);

	void Draw(Shader& shader, Camera& camera);
};

