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

			m_Meshes[0]->GetTransform().MoveY(30.0f);
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
	
}

void Scene4::UnloadResources()
{
	m_Meshes.clear();
	AssetManager::GetInstance().Unload(GetName(), "Grenade");

	this->m_AssetsLoaded = false;
}
