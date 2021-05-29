#include "pch.h"
#include "FirstScene.h"

#include <string>
#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>
#include <glm/vec2.hpp>
#include "Core/App.h"
#include "Utils/Log.h"

FirstScene::FirstScene() :
	AScene{STRINGIFY(FirstScene)}
{
	

}

FirstScene::~FirstScene()
{
}

void FirstScene::RenderUI(Camera& camera)
{
}

void FirstScene::RenderMeshes(Camera& camera)
{
	this->mesh->Draw(camera);
}

void FirstScene::Update(float deltaTime)
{
}

void FirstScene::LoadResources()
{
	// m_Camera = new Camera(glm::radians(45.0f), static_cast<float>(App::Width) / static_cast<float>(App::Height));
	// // Load 
	//  this->shader = new Shader("Content/Shaders/vertShader.glsl", "Content/Shaders/fragShader.glsl");
	//  this->mesh = Mesh::Load("Content/3D_Models/", "teapot", *this->shader);
}

void FirstScene::UnloadResources()
{
	// Unload

}
