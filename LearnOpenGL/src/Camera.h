#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shaderClass.h"

class Camera
{
public:
	glm::vec3 
		Pos, Vel{0.f},
		Dir{ 0.f,0.f,-1.f }, 
		Up{ 0.f,1.f,0.f };
	glm::uvec2 windowSize;
	glm::mat4 camMatrix{ 1.f };

	float speed = 0.1f;
	float sensivtivity = 100.f;
	bool firstClick = true;

	Camera(const uint32_t& width, const uint32_t& height, glm::vec3 position);
	// Updates and exports the camera matrix to the Vertex Shader
	void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
	void Matrix(Shader& shader, const char* uniform);
	// Handles camera inputs
	void Inputs(GLFWwindow* window);
};

