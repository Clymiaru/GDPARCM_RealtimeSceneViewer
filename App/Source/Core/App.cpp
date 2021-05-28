﻿#include "pch.h"
#include "App.h"
#include <ImGui/imgui.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_glfw.h>

#include "SceneManagement/SceneManager.h"

#include "Utils/Log.h"

Uint App::Width;
Uint App::Height;

App::App(const Uint width,
         const Uint height)
{
	Width = width;
	Height = height;
	
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
	SceneManager::GetInstance().LoadScenes({"MainScene"});
	SceneManager::GetInstance().LoadScenes({ "FirstScene" });

	while (!glfwWindowShouldClose(m_Window))
	{
		glfwPollEvents();
	
		glClearColor(0.0f, 0.0f, 0.1f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		SceneManager::GetInstance().RenderScenesMeshes();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		SceneManager::GetInstance().RenderScenesUI();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
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

	m_Window = glfwCreateWindow(Width, Height, "Realtime Scene Viewer", nullptr, nullptr);

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

void App::InitImGui() const
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init((char *)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
}
