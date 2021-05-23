#include "pch.h"
#include "App.h"
#include <ImGui/imgui.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_glfw.h>

#include "Utils/Log.h"

const String BASEPATH = "Content/3D_Models/";
const String INPUTFILE1 = "teapot";

App::App()
{
	InitGlfw();
	InitGlad();
	InitImGui();

	m_Shader = new Shader("Content/Shaders/vertShader.glsl",
                      "Content/Shaders/fragShader.glsl");
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
	// Load Assests
	InitOBJ();

	while (!glfwWindowShouldClose(m_Window))
	{
		/* Poll for and process events */
		glfwPollEvents();
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		/* Render here */
		DisplayOBJ(this->m_Window);

		/////Render assets/////

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

	m_Window = glfwCreateWindow(600, 600, "Hello World", NULL, NULL);

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

void App::InitOBJ()
{
	m_Mesh = Mesh::Load(BASEPATH, INPUTFILE1, *m_Shader);
}

void App::DisplayOBJ(GLFWwindow* window)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	m_Mesh->Draw(glm::mat4());
}


