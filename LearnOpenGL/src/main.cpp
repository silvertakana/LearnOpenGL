#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <thread>
#include <chrono>

#include "Engine.h"
#include "Vertex.h"
#include "Texture.h"
#include "handleFiles.h"
#include "shaderClass.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "Camera.h"
namespace Window {
	static const glm::uvec2 Size{ 1920, 1080 };
	static const float Ratio = Size.x / Size.y;
}
template<class T>
T mapValue(const T& Value, const T& Min1, const T& Max1, const T&Min2, const T& Max2)
{
	return (Value - Min1) / (Max1 - Min1) * (Max2 - Min2) + Min2;
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Vertices coordinates

	GLFWwindow* window = glfwCreateWindow(Window::Size.x, Window::Size.y, "my opengl project", NULL, NULL);
	if (!window)
	{
		std::cout << "unable to create GLFW window.\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, Window::Size.x, Window::Size.y);

	Shader shaderProgram("res/shaders/3D.shader");
	// Vertices coordinates
	GLfloat vertices[] =
	{ //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
		-1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
		 1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
		 1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	GLfloat lightVertices[] =
	{ //     COORDINATES     //
		-0.1f, -0.1f,  0.1f,
		-0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f,  0.1f,
	};

	GLuint lightIndices[] =
	{
		0, 2, 1,
		0, 3, 2,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7,
	};

	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3*sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6*sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8*sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	Shader lightShader("res/shaders/light.shader");
	VAO lightVAO;
	lightVAO.Bind();
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor{ 1.f, 1.f,1.f, 1.f };

	glm::vec3 lightPos{ -0.5f,0.3f,0.5f };
	glm::mat4 lightModel{ 1.f };
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objectPos{ 0.f };
	glm::mat4 objectModel{ 1.f };
	objectModel = glm::translate(objectModel, objectPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	Texture planksTex("res/textures/planks.png", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
	planksTex.texUnit(shaderProgram, "tex0", 0);
	Texture planksSpec("res/textures/planksSpec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
	planksSpec.texUnit(shaderProgram, "tex1", 1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glfwSwapInterval(1);


	size_t frameCount = 0;
	Engine::UpdateDeltaTime();
	Camera camera(Window::Size.x, Window::Size.y, glm::vec3(0.f, 0.1f, 2.f));
	while (!glfwWindowShouldClose(window))
	{
		{
			using namespace std::string_literals;
			if (frameCount % 20 == 0)
				Engine::UpdateFPS();
			glfwSetWindowTitle(window, ("my opengl project - " + std::to_string(Engine::FPS) + "FPS / " + std::to_string(Engine::DeltaTime * 1000) + "ms").c_str());
		}
		Engine::UpdateDeltaTime();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

		camera.Inputs(window);
		camera.UpdateMatrix(45.f, 0.0001f, 100.f);
		//lightColor = { sinf(frameCount/100.f)/2+0.5f, sinf(frameCount / 100.f+20) / 2 + 0.5f,sinf(frameCount / 100.f+40) / 2 + 0.5f, 1.f };
		shaderProgram.Activate();
		if(glfwGetKey(window,GLFW_KEY_E) != GLFW_PRESS )
			glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Pos.x, camera.Pos.y, camera.Pos.z);
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);


		camera.Matrix(shaderProgram, "camMatrix");
		planksSpec.Bind();
		planksTex.Bind();
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
		lightShader.Activate();
		glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

		camera.Matrix(lightShader, "camMatrix");
		
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
		frameCount++;

	}

	glfwDestroyWindow(window);
	glfwTerminate();
}