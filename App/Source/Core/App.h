#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <glad.h>
#include <glm/glm.hpp>	

//#define TINYOBJLOADER_IMPLEMENTATION
//#include "tiny_obj_loader.h"



// TODO: Link error callbacks
// TODO: Window encapsulation
// TODO: Refactor App class

#define numVAOs 1

using namespace std;
using namespace glm;


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
	void LoadColoredOBJ(int order);
	void InitOBJ(GLFWwindow* window);
	void DisplayOBJ(GLFWwindow* window);
};
