#include "pch.h"
#include "App.h"
#include <ImGui/imgui.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_glfw.h>

#include "Utils/Log.h"
#include "ShaderProgramAttachment.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint VBO, EBO;

string basepath = "3D_Models/";
string inputfile1 = basepath + "teapot.obj"; //enclose the obj filename.type in the string
vector <tinyobj::shape_t> shapes; //This vector will hold the MESH data
vector <tinyobj::material_t> materials; //This vector will hold the MATERIAL data

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
	// Load Assests
	InitOBJ(this->m_Window);

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


void App::LoadColoredOBJ(int order)
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, shapes[0].mesh.positions.size() * sizeof(float), &(shapes[0].mesh.positions[0]), GL_STATIC_DRAW);
	glEnableVertexAttribArray(glGetAttribLocation(renderingProgram, "v_vertex"));
	glVertexAttribPointer(glGetAttribLocation(renderingProgram, "v_vertex"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind buffers

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shapes[0].mesh.indices.size() * sizeof(unsigned int), &(shapes[0].mesh.indices[0]), GL_STATIC_DRAW);
	glBindVertexArray(0);

	glBindVertexArray(vao[order]);
}


void App::InitOBJ(GLFWwindow* window)
{
	string err; //error text
	if (tinyobj::LoadObj(shapes, materials, err, inputfile1.c_str(), basepath.c_str())) {
		cout << "Load OBJ: True" << endl;
	}

	else {
		cout << "Load OBJ : False" << endl;
	}

	renderingProgram = createShaderProgram();
	//cout << "Hello test" << endl;
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);

	if (!err.empty()) {//did the OBJ load correctly?
		std::cerr << err << std::endl; // `err` may contain warning message.
	}

	else
		std::cout << "Loaded " << inputfile1 << " with shapes: " << shapes.size() << std::endl; //print out number of meshes described in file

	LoadColoredOBJ(1);
}

void App::DisplayOBJ(GLFWwindow* window)
{
	//glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(vao[0]);
	glUseProgram(renderingProgram);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(glGetAttribLocation(renderingProgram, "v_vertex"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, shapes[0].mesh.indices.size(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


