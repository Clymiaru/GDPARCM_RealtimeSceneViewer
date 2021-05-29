#pragma once
#include <GLFW/glfw3.h>

#include "RenderSystem/Shader.h"

class App
{
public:
	static Uint Width;
	static Uint Height;
	
	App(Uint width, Uint height);
	virtual ~App();
	void Run();

private:
	GLFWwindow* m_Window;
	
	void InitGlfw();
	static void InitGlad();
	void InitImGui() const;

	void Update(float deltaTime);
	void Render();

	double m_Ticks = 0.0;
	Uint32 m_Framecount = 0;
	Uint32 m_FPS = 0;
};
