#include "pch.h"
#include "App.h"
#include <glad.h>
#include <ImGui/imgui.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_glfw.h>

#include "Utils/Log.h"

App::App()
{
	InitGlfw();
	InitGlad();
	InitImGui();
}

App::~App()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}

void App::Run()
{
	while (!glfwWindowShouldClose(m_Window))
	{
		/* Poll for and process events */
		glfwPollEvents();
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		/* Render here */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Demo window");
		ImGui::Button("Hello!");
		ImGui::End();
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		/* Swap front and back buffers */
		glfwSwapBuffers(m_Window);
	}
}

void App::InitGlfw()
{
	const int glfwInitFlag = glfwInit();

	ASSERT(glfwInitFlag == GLFW_TRUE,
			"GLFW cannot be initialized!");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

	ASSERT(m_Window != nullptr,
			"Window cannot be created!");

	glfwMakeContextCurrent(m_Window);
	
}

void App::InitGlad()
{
	const int gladInitFlag = gladLoadGL();
	ASSERT(gladInitFlag == true,
			"GLAD cannot be initialized!");
}

void App::InitImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init((char *)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
}
