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
			Model& model = AssetManager::GetInstance().Acquire("Chair");
			m_Meshes.push_back(new Mesh(model, *shader));
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
	
}

void Scene3::UnloadResources()
{
	AssetManager::GetInstance().Unload(GetName(), "Chair");

	this->m_AssetsLoaded = false;
}