#include "pch.h"
#include "Scene0.h"

#include <string>
#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>
#include <glm/vec2.hpp>

#include "AssetManagement/AssetManager.h"

#include "Core/App.h"

#include "SceneManagement/SceneManager.h"

#include "Utils/Log.h"

Scene0::Scene0() :
	AScene{ STRINGIFY(Scene0) }
{
}

Scene0::~Scene0()
{
}

void Scene0::RenderUI(Camera& camera)
{
}

void Scene0::RenderMeshes(Camera& camera)
{
	for (auto* mesh : m_Meshes)
	{
		mesh->Draw(camera);
	}
}

void Scene0::Update(float deltaTime)
{
	if (!m_AssetsLoaded)
	{
		if (AssetManager::GetInstance().GetAssetsLoaded(GetName()) >= 1)
		{
			m_AssetsLoaded = true;
			Model& model = AssetManager::GetInstance().Acquire("teapot");
			m_Meshes.push_back(new Mesh(model, *shader));
		}
	}
}

void Scene0::LoadResources()
{
	// Load 
	this->shader = new Shader("Content/Shaders/vertShader.glsl", "Content/Shaders/fragShader.glsl");

	AssetManager::GetInstance().LoadAsync(GetName(),
                                                  "teapot",
                                                    "Content/3D_Models/teapot.obj",
                                                   "Content/3D_Models/");

	SceneManager::GetInstance().ActivateScenes({GetName()});
	// this->mesh = Mesh::Load("Content/3D_Models/", "teapot", *this->shader);
}

void Scene0::UnloadResources()
{
}
