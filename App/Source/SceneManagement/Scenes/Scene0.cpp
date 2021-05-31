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
			Model& model_Teapot = AssetManager::GetInstance().Acquire("teapot");
			Model& model_AlienAnimal = AssetManager::GetInstance().Acquire("Alien Animal");
			Model& model_SpaceAirCraft = AssetManager::GetInstance().Acquire("E 45 Aircraft_obj");

			m_Meshes.push_back(new Mesh(model_Teapot, *shader));
			m_Meshes.push_back(new Mesh(model_AlienAnimal, *shader));
			m_Meshes.push_back(new Mesh(model_SpaceAirCraft, *shader));

			// Set position of Spaceship
			m_Meshes[0]->GetTransform().MoveX(-60.0f); 
			m_Meshes[0]->GetTransform().Scale(20.0f, 20.0f, 20.0f);

			// Set position of Spaceship
			m_Meshes[2]->GetTransform().MoveX(-30.0f);
			m_Meshes[2]->GetTransform().RotateY(180.0f);
			m_Meshes[2]->GetTransform().Scale(5.0f, 5.0f, 5.0f);
		}
	}
}

int Scene0::GetMaxAssets()
{
	return this->maxAssets;
}

void Scene0::LoadResources()
{
	// Load 
	this->shader = new Shader("Content/Shaders/vertShader.glsl", "Content/Shaders/fragShader.glsl");

	AssetManager::GetInstance().LoadAsync(GetName(),
                                                  "teapot",
                                                  "Content/3D_Models/teapot.obj",
                                                  "Content/3D_Models/");

	AssetManager::GetInstance().LoadAsync(GetName(),
												  "Alien Animal",
												  "Content/3D_Models/Alien Animal.obj",
												  "Content/3D_Models/");

	AssetManager::GetInstance().LoadAsync(GetName(),
												  "E 45 Aircraft_obj",
												  "Content/3D_Models/E 45 Aircraft_obj.obj",
												  "Content/3D_Models/");

}

void Scene0::UnloadResources()
{
	LOG("Hello Unload!");
	m_Meshes.clear();
	AssetManager::GetInstance().Unload(GetName(), "teapot");
	AssetManager::GetInstance().Unload(GetName(), "Alien Animal");
	AssetManager::GetInstance().Unload(GetName(), "E 45 Aircraft_obj");
	
	this->m_AssetsLoaded = false;
}
