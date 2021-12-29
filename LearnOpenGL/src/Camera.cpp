#include "Camera.h"
#include "Engine.h"
#include <iostream>

Camera::Camera(const uint32_t& width, const uint32_t& height, glm::vec3 position)
	:windowSize(width,height),Pos(position)
{}

void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	glm::mat4 view{ 1.f };
	glm::mat4 proj{ 1.f };
	view = glm::lookAt(Pos, Pos + Dir, Up);
	proj = glm::perspective(glm::radians(45.f), (float)windowSize.x / windowSize.y, nearPlane, farPlane);
	camMatrix = proj * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(camMatrix));
}

void Camera::Inputs(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Vel += (speed*Engine::DeltaTime) * Dir;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Vel += (speed*Engine::DeltaTime) * -glm::normalize(glm::cross(Dir, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Vel += (speed*Engine::DeltaTime) * -Dir;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Vel += (speed*Engine::DeltaTime) * glm::normalize(glm::cross(Dir, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Vel += (speed*Engine::DeltaTime) * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Vel += (speed*Engine::DeltaTime) * -Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.2f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.05f;
	}
	Pos += Vel;
	Vel *= 1 / (1+5.f * Engine::DeltaTime);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		if (firstClick)
		{
			glfwSetCursorPos(window, windowSize.x / 2, windowSize.y / 2);
			firstClick = false;
		}
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glm::dvec2 mousePos;
		glfwGetCursorPos(window, &mousePos.x, &mousePos.y);
		glm::vec2 rotation = sensivtivity * ((glm::vec2)mousePos - (1 / 2.f * (glm::vec2)windowSize)) / (glm::vec2)windowSize;
		
		glm::vec3 newDir = glm::rotate(Dir, glm::radians(-rotation.y), glm::normalize(glm::cross(Dir, Up)));
		if (!((glm::angle(newDir, Up) <= glm::radians(5.f)) or (glm::angle(newDir, -Up) <= glm::radians(5.f))))
		{
			Dir = newDir;
		}
		Dir = glm::rotate(Dir, glm::radians(-rotation.x),Up);
		glfwSetCursorPos(window, windowSize.x / 2, windowSize.y / 2);
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}