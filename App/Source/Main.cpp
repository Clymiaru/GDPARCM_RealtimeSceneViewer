#include "pch.h"
#include <GLFW/glfw3.h>
#include "Utils/Log.h"

int main()
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(1280, 720, "GLFW window", nullptr, nullptr);
	ASSERT(window != nullptr, "Window cannot be set to active!");

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 0.0f, 0.0f ,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	
	glfwTerminate();
}
