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
			Model& model_asteroid = AssetManager::GetInstance().Acquire("A2");
			Model& model_cat = AssetManager::GetInstance().Acquire("12221_Cat_v1_l3");
			Model& model_Decoration = AssetManager::GetInstance().Acquire("katana");

			m_Meshes.push_back(new Mesh(model_asteroid, *shader));
			m_Meshes.push_back(new Mesh(model_cat, *shader));
			m_Meshes.push_back(new Mesh(model_Decoration, *shader));

			// Asteriod
			m_Meshes[0]->GetTransform().MoveX(90.0f);
			m_Meshes[0]->GetTransform().Scale(10.0f, 10.0f, 10.0f);

			// Rotate Cat
			m_Meshes[1]->GetTransform().MoveX(60.0f);
			m_Meshes[1]->GetTransform().RotateX(-90.0f);
			
			// Move Decoration
			m_Meshes[2]->GetTransform().MoveX(30.0f);
			m_Meshes[2]->GetTransform().MoveY(30.0f);
		}
	}
}

int Scene1::GetMaxAssets()
{
	return this->maxAssets;
}

void Scene1::LoadResources()
{
	// Load katana
	this->shader = new Shader("Content/Shaders/vertShader.glsl", "Content/Shaders/fragShader.glsl");

	AssetManager::GetInstance().LoadAsync(GetName(),
                                                   "A2",
                                                   "Content/3D_Models/A2.obj",
                                                   "Content/3D_Models/");
	
	AssetManager::GetInstance().LoadAsync(GetName(),
                                                   "12221_Cat_v1_l3",
                                                   "Content/3D_Models/12221_Cat_v1_l3.obj",
                                                   "Content/3D_Models/");
	
	AssetManager::GetInstance().LoadAsync(GetName(),
                                                   "katana",
                                                   "Content/3D_Models/katana.obj",
                                                   "Content/3D_Models/");

}

void Scene1::UnloadResources()
{
	m_Meshes.clear();
	AssetManager::GetInstance().Unload(GetName(), "A2");
	AssetManager::GetInstance().Unload(GetName(), "12221_Cat_v1_l3");
	AssetManager::GetInstance().Unload(GetName(), "katana");

	this->m_AssetsLoaded = false;
}
