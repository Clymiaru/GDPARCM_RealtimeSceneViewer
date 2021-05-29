#include "pch.h"
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
	SceneManager::GetInstance().LoadScenes({"MainScene", "FirstScene"});
	double now = glfwGetTime();
	double prev = 0.0;
	
	while (!glfwWindowShouldClose(m_Window))
	{
		prev = now;
		
		glfwPollEvents();

		now = glfwGetTime();
		Update(now - prev);

		Render();
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
	ASSERT(gladInitFlag == GL_TRUE,
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

void App::Update(float deltaTime)
{
	m_Ticks += deltaTime;
	m_Framecount++;

	if (m_Ticks > 1.0f)
	{
		m_FPS = m_Framecount;
		m_Framecount = 0;
		m_Ticks = 0;
	}
}

void App::Render()
{
	glEnable(GL_DEPTH_TEST);  
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
		
	glClearColor(0.0f, 0.0f, 0.1f, 1.00f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glCullFace(GL_FRONT);  
	glFrontFace(GL_CCW); 
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
		
	SceneManager::GetInstance().RenderScenesMeshes();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoSavedSettings;
	windowFlags |= ImGuiWindowFlags_NoTitleBar;
	windowFlags |= ImGuiWindowFlags_NoScrollbar;
	windowFlags |= ImGuiWindowFlags_NoMove;
	windowFlags |= ImGuiWindowFlags_NoResize;

	ImGui::SetWindowFontScale(3.8);

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(viewport->WorkPos.x,
                                   viewport->WorkPos.y),
                                     ImGuiCond_Once);

	ImGui::SetNextWindowSize(ImVec2(75.0f,
                                   30.0f),
                                     ImGuiCond_Once);

	if(!ImGui::Begin("FPSCounter", nullptr, windowFlags))
	{
		ImGui::End();
	}
	else
	{
		ImGui::TextColored({1.0f, 1.0f, 0.0f, 1.0f}, "FPS: %d", m_FPS);
		ImGui::End();
	}

	ImGui::SetWindowFontScale(1.0);
	SceneManager::GetInstance().RenderScenesUI();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
	glfwSwapBuffers(m_Window);
}

