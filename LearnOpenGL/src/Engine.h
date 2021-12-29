#pragma once
#include <glfw/glfw3.h>
class Engine
{
private:
	static float lastFrameTime;
public:
	static float DeltaTime;
	static float FPS;
	static void UpdateDeltaTime();
	static void UpdateFPS();
};