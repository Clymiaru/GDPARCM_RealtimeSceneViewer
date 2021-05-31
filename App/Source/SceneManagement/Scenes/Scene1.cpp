#include "pch.h"
#include "Scene1.h"

#include "AssetManagement/AssetManager.h"

#include "SceneManagement/SceneManager.h"

Scene1::Scene1() :
	AScene{ STRINGIFY(Scene1) }
{
}

Scene1::~Scene1()
{
}

void Scene1::RenderUI(Camera& camera)
{
}

void Scene1::RenderMeshes(Camera& camera)
{
	for (auto* mesh : m_Meshes)
	{
		mesh->Draw(camera);
	}
}

void Scene1::Update(float deltaTime)
{
	if (!m_AssetsLoaded)
	{
		if (AssetManager::GetInstance().GetAssetsLoaded(GetName()) >= 1)
		{
			m_AssetsLoaded = true;
			Model& model = AssetManager::GetInstance().Acquire("A2");
			m_Meshes.push_back(new Mesh(model, *shader));
		}
	}
}

int Scene1::GetMaxAssets()
{
	return this->maxAssets;
}

void Scene1::LoadResources()
{
	// Load 
	this->shader = new Shader("Content/Shaders/vertShader.glsl", "Content/Shaders/fragShader.glsl");

	AssetManager::GetInstance().LoadAsync(GetName(),
                                                  "A2",
                                                    "Content/3D_Models/A2.obj",
                                                   "Content/3D_Models/");

}

void Scene1::UnloadResources()
{
	AssetManager::GetInstance().Unload(GetName(), "A2");
	this->shader->Unbind();
	delete this->shader;

	this->m_AssetsLoaded = false;
}
