#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLfloat verticies[]
	{
		 0.5f,-0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f,-0.5f, 0.0f,
	};

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


	GLuint shaderProgram = glCreateProgram();//the shader program
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);//the vertex shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//the fragment shader
		char* vertexShaderSource, * fragmentShaderSource;//vertex and fragment shader source
		//load the shader file and change data type from std::string to char*
		{
			auto [vertex, fragment] = loadShader("res/shaders/test.shader");
			vertexShaderSource = strcpy(new char[vertex.size() + 1], vertex.c_str());
			fragmentShaderSource = strcpy(new char[fragment.size() + 1], fragment.c_str());
		}
		//putting the shader source into the shader
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		//compile the shader
		glCompileShader(vertexShader);
		glCompileShader(fragmentShader);
		//attach the shader to the program
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		//link the program with openGL
		glLinkProgram(shaderProgram);
		//delete the unuse shader
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		delete vertexShaderSource;
		delete fragmentShaderSource;
	}
	GLuint VAO, VBO;
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.149, 0.301, 0.458, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwDestroyWindow(window);
	glfwTerminate();
}