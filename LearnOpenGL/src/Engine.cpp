#include "Engine.h"

void Engine::UpdateDeltaTime()
{
	double currentFrameTime = glfwGetTime();
	DeltaTime = (currentFrameTime - lastFrameTime);
	lastFrameTime = currentFrameTime;
}
void Engine::UpdateFPS()
{
	FPS = 1 / DeltaTime;
}

float Engine::DeltaTime = 0;
float Engine::FPS = 0;
float Engine::lastFrameTime = 0;