#pragma once
#include <GLFW/glfw3.h>

// TODO: Link error callbacks
// TODO: Window encapsulation
// TODO: Refactor App class

class App
{
public:
	App();
	virtual ~App();
	void Run();
private:
	GLFWwindow* m_Window;
	
	void InitGlfw();
	void InitGlad();
	void InitImGui();
};
