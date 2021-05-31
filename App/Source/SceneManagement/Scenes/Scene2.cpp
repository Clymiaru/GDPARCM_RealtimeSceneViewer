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
				Model& model_bunny = AssetManager::GetInstance().Acquire("bunny");
				m_Meshes.push_back(new Mesh(model_bunny, *shader));
				
				Model& model_Human = AssetManager::GetInstance().Acquire("FinalBaseMesh");
				m_Meshes.push_back(new Mesh(model_Human, *shader));

				Model& model_Car = AssetManager::GetInstance().Acquire("uploads_files_2792345_Koenigsegg");
				m_Meshes.push_back(new Mesh(model_Car, *shader));


				// bunny 
				m_Meshes[0]->GetTransform().MoveX(120.0f);
				m_Meshes[0]->GetTransform().Scale(30.0f, 30.0f, 30.0f);

				// human 
				m_Meshes[1]->GetTransform().MoveX(30.0f);
				m_Meshes[1]->GetTransform().MoveZ(10.0f);

				// car
				m_Meshes[2]->GetTransform().MoveX(150.0f);
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

	AssetManager::GetInstance().LoadAsync(GetName(),
											  "FinalBaseMesh",
												"Content/3D_Models/FinalBaseMesh.obj",
											   "Content/3D_Models/");

	AssetManager::GetInstance().LoadAsync(GetName(),
											  "uploads_files_2792345_Koenigsegg",
												"Content/3D_Models/uploads_files_2792345_Koenigsegg.obj",
											   "Content/3D_Models/");

}

void Scene2::UnloadResources()
{
	m_Meshes.clear();
	AssetManager::GetInstance().Unload(GetName(), "bunny");
	AssetManager::GetInstance().Unload(GetName(), "FinalBaseMesh");
	AssetManager::GetInstance().Unload(GetName(), "uploads_files_2792345_Koenigsegg");

	this->m_AssetsLoaded = false;
}
