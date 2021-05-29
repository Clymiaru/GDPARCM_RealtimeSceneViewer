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

void FirstScene::RenderUI()
{
}

void FirstScene::RenderMeshes()
{
	//this->mesh->Draw(m_Camera->GetViewProjectionMatrix());
}

void FirstScene::Update(float deltaTime)
{
}

void FirstScene::LoadResources()
{
	// Load 
	// this->shader = new Shader("Content/Shaders/vertShader.glsl", "Content/Shaders/fragShader.glsl");
	// this->mesh = Mesh::Load("Content/3D_Models/", "teapot", *this->shader);
}

void FirstScene::UnloadResources()
{
	// Unload

}
