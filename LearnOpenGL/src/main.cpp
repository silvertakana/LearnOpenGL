#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "handleFiles.h"
#include "shaderClass.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Vertices coordinates
	

	GLFWwindow* window = glfwCreateWindow(500, 500, "my opengl project", NULL, NULL);
	if (!window)
	{
		std::cout << "unable to create GLFW window.\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 500, 500);

	Shader shaderProgram("res/shaders/test.shader");
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};
	GLuint indicies[] =
	{
		0, 3, 5,
		3, 2, 4,
		5, 4, 1,
	};
	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indicies, sizeof(indicies));
	VAO1.LinkVBO(VBO1,0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	shaderProgram.Activate();
	VAO1.Bind();
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.149, 0.301, 0.458, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, sizeof(indicies)/sizeof(GLuint), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
}