#include "pch.h"
#include "Scene2.h"

#include "AssetManagement/AssetManager.h"

#include "SceneManagement/SceneManager.h"

Scene2::Scene2() :
	AScene{ STRINGIFY(Scene2) }
{
}

Scene2::~Scene2()
{
}

void Scene2::RenderUI(Camera& camera)
{
}

void Scene2::RenderMeshes(Camera& camera)
{
	for (auto* mesh : m_Meshes)
	{
		mesh->Draw(camera);
	}
}

void Scene2::Update(float deltaTime)
{
	if (!m_AssetsLoaded)
		{
			if (AssetManager::GetInstance().GetAssetsLoaded(GetName()) >= 1)
			{
				m_AssetsLoaded = true;
				Model& model = AssetManager::GetInstance().Acquire("bunny");
				m_Meshes.push_back(new Mesh(model, *shader));
			}
		}
}

int Scene2::GetMaxAssets()
{
	return this->maxAssets;
}

void Scene2::LoadResources()
{
	// Load 
	this->shader = new Shader("Content/Shaders/vertShader.glsl", "Content/Shaders/fragShader.glsl");

	AssetManager::GetInstance().LoadAsync(GetName(),
											  "bunny",
												"Content/3D_Models/bunny.obj",
											   "Content/3D_Models/");

}

void Scene2::UnloadResources()
{
	AssetManager::GetInstance().Unload(GetName(), "bunny");

	this->m_AssetsLoaded = false;
}
