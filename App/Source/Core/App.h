#pragma once
#include <GLFW/glfw3.h>

#include "Utils/TypeAlias.h"
#include "RenderSystem/Camera.h"

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
	Camera* m_MainCamera;
	
	void InitGlfw();
	static void InitGlad();
	void InitImGui() const;

	void Initialize();
	void Update(float deltaTime);
	void Render();
	void Deinitialize();

	double m_Ticks = 0.0;
	Uint32 m_Framecount = 0;
	Uint32 m_FPS = 0;
};
