#include "pch.h"
#include "FirstScene.h"

#include <string>

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

#include <glm/vec2.hpp>

#include "Core/App.h"

#include "Utils/Log.h"

FirstScene::FirstScene() :
	AScene{ STRINGIFY(FirstScene) },
	m_Progress{ 0.1f }
{

}

FirstScene::~FirstScene()
{
}

void FirstScene::RenderUI()
{
}

void FirstScene::RenderMeshes()
{
	// Render Meshes at this scene
	static glm::mat4 transform = glm::mat4(1.0f);

	// move
	//transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, -0.01f));
	

	//rotate
	//transform = glm::rotate(transform, 0.001f, glm::vec3(1.0f, 0.0f, 0.0f));
	this->mesh->Draw(transform);
}

void FirstScene::LoadResources()
{
	// Load 
	this->shader = new Shader("Content/Shaders/vertShader.glsl", "Content/Shaders/fragShader.glsl");
	this->mesh = Mesh::Load("Content/3D_Models/", "teapot", *this->shader);
}

void FirstScene::UnloadResources()
{
	// Unload

}
