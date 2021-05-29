#include "pch.h"
#include "Scene0.h"

#include <string>
#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>
#include <glm/vec2.hpp>
#include "Core/App.h"
#include "Utils/Log.h"

Scene0::Scene0() :
	AScene{ STRINGIFY(Scene0) }
{
}

Scene0::~Scene0()
{
}

void Scene0::RenderUI()
{
}

void Scene0::RenderMeshes()
{
	this->mesh->Draw(m_Camera->GetViewProjectionMatrix());
}

void Scene0::LoadResources()
{
	// Load 
	this->shader = new Shader("Content/Shaders/vertShader.glsl", "Content/Shaders/fragShader.glsl");
	this->mesh = Mesh::Load("Content/3D_Models/", "teapot", *this->shader);
}

void Scene0::UnloadResources()
{
}
