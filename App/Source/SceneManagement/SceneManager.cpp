#include "pch.h"
#include "SceneManager.h"

#include "Utils/Log.h"

List<AScene*>::const_iterator FindSceneOfNameInList(StringRef nameToFind, const List<AScene*>& sceneList)
{
	auto foundScene =
		std::find_if(sceneList.begin(), sceneList.end(),
					 [nameToFind](AScene* other) -> bool
						  {
						      return nameToFind == other->GetName();
						  });
	
	return foundScene;
}

SceneManager& SceneManager::GetInstance()
{
	static SceneManager instance;
	return instance;
}

void SceneManager::SetMainCamera(Camera& mainCamera)
{
	m_Camera = &mainCamera;
}

void SceneManager::RegisterScenes(List<AScene*> scenes)
{
	for (AScene* scene : scenes)
	{
		ASSERT(scene != nullptr,
			  "Attempting to register a null scene!");

		const String sceneName = scene->GetName();
		AScene* foundScene = m_SceneTable[sceneName];

		if (foundScene == nullptr)
		{
			m_SceneTable[sceneName] = scene;
		}

		else
		{
			LOG("Scene [" << sceneName.c_str() << "] has already been registered!");
		}
	}
}

void SceneManager::LoadScenes(List<String> sceneNames)
{
	for (String sceneName : sceneNames)
	{
		if (!IsSceneRegistered(sceneName))
		{
			LOG("Scene [" << sceneName << "] is not yet registered!");
			continue;
		}
		
		auto foundLoadedScene = FindSceneOfNameInList(sceneName, m_LoadedScenes);
		if (foundLoadedScene != m_LoadedScenes.end())
		{
			LOG("Scene [" << sceneName << "] is already loaded!");
			continue;
		}
		
		auto* toLoad = GetSceneOfName(sceneName);
		// mutex.lock();
		m_LoadedScenes.push_back(toLoad);
		// mutex.unlock();

		// Way to get all asset count for view all.
		toLoad->Load();
	}
}

void SceneManager::ActivateScenes(List<String> sceneNames)
{
	for (String sceneName : sceneNames)
	{
		if (!IsSceneRegistered(sceneName))
		{
			LOG("Scene [" << sceneName << "] is not yet registered!");
			continue;
		}
		
		auto foundLoadedScene = FindSceneOfNameInList(sceneName, m_LoadedScenes);
		if (foundLoadedScene == m_LoadedScenes.end())
		{
			LOG("Scene [" << sceneName << "] is not yet loaded!");
			continue;
		}

		auto foundActiveScene = FindSceneOfNameInList(sceneName, m_ActiveScenes);
		if (foundActiveScene != m_ActiveScenes.end())
		{
			LOG("Scene [" << sceneName << "] is already active!");
			continue;
		}

		(*foundLoadedScene)->SetCamera(*m_Camera);
		m_ActiveScenes.push_back(*foundLoadedScene);
	}
}

void SceneManager::UnloadScenes(List<String> sceneNames)
{
	for (String sceneName : sceneNames)
	{
		if (!IsSceneRegistered(sceneName))
		{
			LOG("Scene [" << sceneName << "] is not yet registered!");
			continue;
		}
		
		auto foundLoadedScene = FindSceneOfNameInList(sceneName, m_LoadedScenes);
		if (foundLoadedScene == m_LoadedScenes.end())
		{
			LOG("Scene [" << sceneName << "] is not yet loaded!");
			continue;
		}

		auto foundActiveScene = FindSceneOfNameInList(sceneName, m_ActiveScenes);
		if (foundActiveScene != m_ActiveScenes.end())
		{
			m_ActiveScenes.erase(foundActiveScene);
		}
		
		(*foundLoadedScene)->Unload();
	}
}

void SceneManager::RenderScenesUI()
{
	for (AScene* activeScene : m_ActiveScenes)
	{
		activeScene->RenderUI(*m_Camera);
	}
}

void SceneManager::RenderScenesMeshes()
{
	for (AScene* activeScene : m_ActiveScenes)
	{
		activeScene->RenderMeshes(*m_Camera);
	}
}

void SceneManager::UpdateScenes(const float deltaTime)
{
	for (AScene* activeScene : m_ActiveScenes)
	{
		activeScene->Update(deltaTime);
	}
}

AScene* SceneManager::GetSceneOfName(StringRef sceneName)
{
	return m_SceneTable[sceneName]; 
}

bool SceneManager::IsSceneRegistered(StringRef sceneName)
{
	AScene* scene = GetSceneOfName(sceneName);

	if (scene == nullptr)
	{
		LOG("Scene [" << sceneName << "] is either not registered or doesn't exist!");
	}
	
	return scene != nullptr;
}