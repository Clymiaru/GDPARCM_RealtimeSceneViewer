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
		m_LoadedScenes.push_back(toLoad);

		// Way to get all asset count for view all.
		toLoad->Load();
	}
}

void SceneManager::ActivateScenes()
{
	while (!m_ActivateSceneQueue.empty())
	{
		auto* scene = m_ActivateSceneQueue.front();
		m_ActivateSceneQueue.pop();

		m_ActiveScenes.push_back(scene);
	}
}

void SceneManager::DeactivateScenes()
{
	while (!m_DeactivateSceneQueue.empty())
	{
		auto* scene = m_DeactivateSceneQueue.front();
		m_DeactivateSceneQueue.pop();

		int index = -1;
		for (int i = 0; i < m_ActiveScenes.size(); i++)
		{
			if (m_ActiveScenes[i]->GetName() == scene->GetName())
			{
				index = i;
				break;
			}
		}

		if (index != -1)
		{
			m_ActiveScenes.erase(m_ActiveScenes.begin() + index);
		}
	}
}

void SceneManager::MarkScenesToActivate(List<String> sceneNames)
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
			//LOG("Scene [" << sceneName << "] is not yet loaded!");
			continue;
		}

		auto foundActiveScene = FindSceneOfNameInList(sceneName, m_ActiveScenes);
		if (foundActiveScene != m_ActiveScenes.end())
		{
			LOG("Scene [" << sceneName << "] is already active!");
			continue;
		}

		(*foundLoadedScene)->SetCamera(*m_Camera);
		m_ActivateSceneQueue.push(*foundLoadedScene);
	}
}

void SceneManager::MarkScenesToDeactivate(List<String> sceneNames)
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
			//LOG("Scene [" << sceneName << "] is not yet loaded!");
			continue;
		}

		auto foundActiveScene = FindSceneOfNameInList(sceneName, m_ActiveScenes);
		if (foundActiveScene != m_ActiveScenes.end())
		{
			m_DeactivateSceneQueue.push(*foundLoadedScene);
			continue;
		}
		LOG("Scene [" << sceneName << "] is not yet activated!");
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
		m_LoadedScenes.erase(foundLoadedScene);

	}
}

int SceneManager::GetMaxAssetOfScene(StringRef sceneName)
{
	if (!IsSceneRegistered(sceneName))
	{
		LOG("Scene [" << sceneName << "] is not yet registered!");
		return -1;
	}

	return m_SceneTable[sceneName]->GetMaxAssets();
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