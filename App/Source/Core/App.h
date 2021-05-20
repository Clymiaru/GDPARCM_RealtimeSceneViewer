#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <glad.h>
#include <glm/glm.hpp>	

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

	GLuint renderingProgram;
	GLuint vao[numVAOs];
	GLuint VBO1, CBO1, EBO1, VBO2, CBO2, EBO2, VBO3, CBO3, EBO3;

	string basepath = "3D_Models/";
	string inputfile1 = basepath + "teapot.obj"; //enclose the obj filename.type in the string
	
	
	void InitGlfw();
	void InitGlad();
	void InitImGui();
};
