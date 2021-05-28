#include "pch.h"
#include "SceneManager.h"

#include "Utils/Log.h"

SceneManager& SceneManager::GetInstance()
{
	static SceneManager instance;
	return instance;
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
			break;
		}
		
		LOG("Scene [" << sceneName.c_str() << "] has already been registered!");
	}
}

void SceneManager::LoadScenes(List<String> sceneNames)
{
	for (String sceneName : sceneNames)
	{
		if (IsSceneActive(sceneName))
		{
			LOG("Scene [" << sceneName << "] is already loaded!");
			break;
		}
		
		AScene* foundScene = m_SceneTable[sceneName];
		foundScene->Load();
		m_ActiveScenes.push_back(foundScene);
	}
}

void SceneManager::UnloadScenes(List<String> sceneNames)
{
	for (String sceneName : sceneNames)
	{
		if (!IsSceneActive(sceneName))
		{
			LOG("Scene [" << sceneName << "] is not yet loaded!");
			break;
		}

		AScene* foundScene = GetSceneOfName(sceneName);
		m_ActiveScenes.clear();
		foundScene->Unload();
	}
}

void SceneManager::RenderScenesUI()
{
	for (AScene* activeScene : m_ActiveScenes)
	{
		activeScene->RenderUI();
	}
}

void SceneManager::RenderScenesMeshes()
{
	for (AScene* activeScene : m_ActiveScenes)
	{
		activeScene->RenderMeshes();
	}
}

AScene* SceneManager::GetSceneOfName(StringRef sceneName)
{
	return m_SceneTable[sceneName]; 
}

bool SceneManager::IsSceneActive(StringRef sceneName)
{
	if (!DoesSceneExist(sceneName))
	{
		return false;
	}

	auto findSceneOfName = [sceneName](AScene* other) -> bool
	{
		return other->GetName() == sceneName;
	};
	const auto foundActiveScene = std::ranges::find_if(m_ActiveScenes, findSceneOfName);

	return foundActiveScene != m_ActiveScenes.end();
}

bool SceneManager::DoesSceneExist(StringRef sceneName)
{
	AScene* scene = GetSceneOfName(sceneName);

	if (scene == nullptr)
	{
		LOG("Scene [" << sceneName << "] is either not registered or doesn't exist!");
	}
	
	return scene != nullptr;
}
