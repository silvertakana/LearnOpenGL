#include "Mesh.h"
#include "Engine.h"
#include <iostream>
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

	// Vertices coordinates
	Vertex vertices[] =
	{ //       COORDINATES      /         COLORS         /        TexCoord        /      NORMALS     //
		{{ -1.0f,  0.0f,  1.0f }, {  0.0f,  1.0f,  0.0f }, {  1.0f,  1.0f,  1.0f }, {  0.0f,  0.0f }},
		{{ -1.0f,  0.0f, -1.0f }, {  0.0f,  1.0f,  0.0f }, {  1.0f,  1.0f,  1.0f }, {  0.0f,  1.0f }},
		{{  1.0f,  0.0f, -1.0f }, {  0.0f,  1.0f,  0.0f }, {  1.0f,  1.0f,  1.0f }, {  1.0f,  1.0f }},
		{{  1.0f,  0.0f,  1.0f }, {  0.0f,  1.0f,  0.0f }, {  1.0f,  1.0f,  1.0f }, {  1.0f,  0.0f }}
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	Vertex lightVertices[] =
	{ //     COORDINATES     //
		{{ -0.1f, -0.1f,  0.1f}},
		{{ -0.1f, -0.1f, -0.1f}},
		{{  0.1f, -0.1f, -0.1f}},
		{{  0.1f, -0.1f,  0.1f}},
		{{ -0.1f,  0.1f,  0.1f}},
		{{ -0.1f,  0.1f, -0.1f}},
		{{  0.1f,  0.1f, -0.1f}},
		{{  0.1f,  0.1f,  0.1f}},
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
	Texture textures[]
	{
		{"res/textures/planks.png",     "difuse",   0, GL_RGB, GL_UNSIGNED_BYTE},
		{"res/textures/planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE},
	};

	Shader shaderProgram("res/shaders/3D.shader"   );
	std::vector<Vertex>  verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex ));
	std::vector<GLuint>  ind  (indices,  indices  + sizeof(indices ) / sizeof(GLuint ));
	std::vector<Texture> tex  (textures, textures + sizeof(textures) / sizeof(Texture));
	Mesh floor(verts, ind, tex);

	Shader lightShader  ("res/shaders/light.shader");
	std::vector<Vertex>  lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector<GLuint>  lightInd  (lightIndices,  lightIndices  + sizeof(lightIndices ) / sizeof(GLuint));
	Mesh light(lightVerts, lightInd, tex);


	glm::vec4 lightColor{ 1.f, 1.f,1.f, 1.f };

	glm::vec3 lightPos{ -0.5f,0.3f,0.5f };
	glm::mat4 lightModel{ 1.f };
	lightModel = glm::translate(lightModel, lightPos);
	lightModel = glm::rotate(lightModel, glm::radians(40.f), glm::vec3(0.0f, 0.0f, 1.0f));
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
		
		floor.Draw(shaderProgram, camera);
		light.Draw(lightShader, camera);

		glfwSwapBuffers(window);
		glfwPollEvents();
		frameCount++;

	}

	glfwDestroyWindow(window);
	glfwTerminate();
}