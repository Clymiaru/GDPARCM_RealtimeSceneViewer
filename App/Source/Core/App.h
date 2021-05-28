#pragma once
#include <GLFW/glfw3.h>

#include "RenderSystem/Mesh.h"
#include "RenderSystem/Shader.h"

// TODO: Link error callbacks
// TODO: Window encapsulation
// TODO: Refactor App class

// #define numVAOs 1

// using namespace std;
// using namespace glm; 
// ^
// Don't do this at least in header files as it can cause problems in the future.
// Like using namespace of multiple libraries and those multiple
// libraries have functions of the same name

class App
{
public:
	App();
	virtual ~App();
	void Run();

private:
	GLFWwindow* m_Window;
	Shader* m_Shader;
	Mesh* m_Mesh;
	
	void InitGlfw();
	void InitGlad();
	void InitImGui();
};
