#include "Mesh.h"
#include <map>

Mesh::Mesh(std::vector<Vertex> i_verticies, std::vector<GLuint> i_indices, std::vector<Texture> i_textures)
	:vertices(i_verticies), indices(i_indices), textures(i_textures)
{
	VAO.Bind();
	VBO VBO1(vertices);
	EBO EBO1(indices);
	VAO.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Position));
	VAO.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	VAO.LinkAttrib(VBO1, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Color));
	VAO.LinkAttrib(VBO1, 3, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, TexUV));

	VAO.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
}

void Mesh::Draw(Shader & shader, Camera & camera)
{
	shader.Activate();
	VAO.Bind();
	std::map<std::string, size_t> TextureCounts;
	for (size_t i = 0;i < textures.size();i++)
	{
		std::string type = textures[i].type;

		textures[i].texUnit(shader, (type + std::to_string(TextureCounts[type]++)).c_str(), i);
		textures[i].Bind();
	}
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Pos.x, camera.Pos.y, camera.Pos.z);
	camera.Matrix(shader,"camMatrix");
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}