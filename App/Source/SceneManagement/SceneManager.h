#pragma once

#include "Utils/TypeAlias.h"

#include "AScene.h"
class SceneManager final
{
public:
	static SceneManager& GetInstance();
	~SceneManager() = default;

	// TODO: Ask if all the scenes will be loaded all at once

	void RegisterScenes(List<AScene*> scenes);
	
	void LoadScenes(List<String> sceneNames);
	void LoadScenesAsync(List<String> sceneNames);
	
	void UnloadScenes(List<String> sceneNames);

	void RenderScenesUI();
	void RenderScenesMeshes();

private:
	List<AScene*> m_ActiveScenes;
	HashTable<String, AScene*> m_SceneTable;

	AScene* GetSceneOfName(StringRef sceneName);
	bool IsSceneActive(StringRef sceneName);
	bool DoesSceneExist(StringRef sceneName);
};
