#include "pch.h"
#include "Scene4.h"

#include "AssetManagement/AssetManager.h"

#include "SceneManagement/SceneManager.h"

Scene4::Scene4() :
	AScene{ STRINGIFY(Scene4) }
{
}

Scene4::~Scene4()
{
}

void Scene4::RenderUI(Camera& camera)
{
}

void Scene4::RenderMeshes(Camera& camera)
{
	for (auto* mesh : m_Meshes)
	{
		mesh->Draw(camera);
	}
}

void Scene4::Update(float deltaTime)
{
	if (!m_AssetsLoaded)
	{
		if (AssetManager::GetInstance().GetAssetsLoaded(GetName()) >= 1)
		{
			m_AssetsLoaded = true;
			Model& model_grenade = AssetManager::GetInstance().Acquire("Grenade");
			m_Meshes.push_back(new Mesh(model_grenade, *shader));

			Model& model_character2 = AssetManager::GetInstance().Acquire("character_2");
			m_Meshes.push_back(new Mesh(model_character2, *shader));

			Model& model_hand = AssetManager::GetInstance().Acquire("12683_hand_v1_FINAL");
			m_Meshes.push_back(new Mesh(model_hand, *shader));

			// grenade
			m_Meshes[0]->GetTransform().MoveY(30.0f);

			// character 2
			m_Meshes[1]->GetTransform().MoveX(-60.0f);
			m_Meshes[1]->GetTransform().MoveY(-90.0f);
			m_Meshes[1]->GetTransform().Scale(2.0f, 2.0f, 2.0f);

			// Hand
			m_Meshes[2]->GetTransform().MoveX(-.0f);
			m_Meshes[2]->GetTransform().MoveY(-90.0f);
			m_Meshes[2]->GetTransform().SetScale(0.5f, 0.5f, 0.5f);
		}
	}
}

int Scene4::GetMaxAssets()
{
	return this->maxAssets;
}

void Scene4::LoadResources()
{
	// Load 
	this->shader = new Shader("Content/Shaders/vertShader.glsl", "Content/Shaders/fragShader.glsl");

	AssetManager::GetInstance().LoadAsync(GetName(),
                                                  "Grenade",
                                                    "Content/3D_Models/Grenade.obj",
                                                   "Content/3D_Models/");

	AssetManager::GetInstance().LoadAsync(GetName(),
                                                  "character_2",
                                                    "Content/3D_Models/character_2.obj",
                                                   "Content/3D_Models/");

	AssetManager::GetInstance().LoadAsync(GetName(),
                                                  "12683_hand_v1_FINAL",
                                                    "Content/3D_Models/12683_hand_v1_FINAL.obj",
                                                   "Content/3D_Models/");
	
}

void Scene4::UnloadResources()
{
	m_Meshes.clear();
	AssetManager::GetInstance().Unload(GetName(), "Grenade");
	AssetManager::GetInstance().Unload(GetName(), "character_2");
	AssetManager::GetInstance().Unload(GetName(), "12683_hand_v1_FINAL");

	this->m_AssetsLoaded = false;
}
