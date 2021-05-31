#include "pch.h"
#include "Scene3.h"

#include "AssetManagement/AssetManager.h"

#include "SceneManagement/SceneManager.h"

Scene3::Scene3() :
	AScene{ STRINGIFY(Scene3) }
{
}

Scene3::~Scene3()
{
}

void Scene3::RenderUI(Camera& camera)
{
}

void Scene3::RenderMeshes(Camera& camera)
{
	for (auto* mesh : m_Meshes)
	{
		mesh->Draw(camera);
	}
}

void Scene3::Update(float deltaTime)
{
	if (!m_AssetsLoaded)
	{
		if (AssetManager::GetInstance().GetAssetsLoaded(GetName()) >= 1)
		{
			m_AssetsLoaded = true;

			Model& model_chair = AssetManager::GetInstance().Acquire("Chair");
			m_Meshes.push_back(new Mesh(model_chair, *shader));

			Model& model_Axe = AssetManager::GetInstance().Acquire("Axe");
			m_Meshes.push_back(new Mesh(model_Axe, *shader));

			Model& model_character = AssetManager::GetInstance().Acquire("character");
			m_Meshes.push_back(new Mesh(model_character, *shader));

			// Chair
			m_Meshes[0]->GetTransform().MoveY(-50.0f);
			m_Meshes[0]->GetTransform().RotateY(180.0f);

			// Axe
			m_Meshes[1]->GetTransform().MoveX(50.0f);
			m_Meshes[1]->GetTransform().MoveY(-30.0f);

			// chopper
			m_Meshes[2]->GetTransform().MoveX(-120.0f);
			m_Meshes[2]->GetTransform().Scale(30.0f, 30.0f, 30.0f);
		}
	}
}

int Scene3::GetMaxAssets()
{
	return this->maxAssets;
}

void Scene3::LoadResources()
{
	// Load 
	this->shader = new Shader("Content/Shaders/vertShader.glsl", "Content/Shaders/fragShader.glsl");

	AssetManager::GetInstance().LoadAsync(GetName(),
                                                  "Chair",
                                                    "Content/3D_Models/Chair.obj",
                                                   "Content/3D_Models/");
	
	AssetManager::GetInstance().LoadAsync(GetName(),
                                                  "Axe",
                                                    "Content/3D_Models/Axe.obj",
                                                   "Content/3D_Models/");
	
	AssetManager::GetInstance().LoadAsync(GetName(),
                                                  "character",
                                                    "Content/3D_Models/character.obj",
                                                   "Content/3D_Models/");
	
}

void Scene3::UnloadResources()
{
	m_Meshes.clear();
	AssetManager::GetInstance().Unload(GetName(), "Chair");
	AssetManager::GetInstance().Unload(GetName(), "Axe");
	AssetManager::GetInstance().Unload(GetName(), "character");

	this->m_AssetsLoaded = false;
}