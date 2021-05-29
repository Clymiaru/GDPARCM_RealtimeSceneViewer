#pragma once

#include "Utils/TypeAlias.h"

#include "AScene.h"
class MainScene;

class SceneManager final
{
public:
	static SceneManager& GetInstance();
	~SceneManager() = default;

	void SetMainCamera(Camera& mainCamera);
	void RegisterScenes(List<AScene*> scenes);
	
	void LoadScenes(List<String> sceneNames);
	// void LoadScenesAsync(List<String> sceneNames);

	void ActivateScenes(List<String> sceneNames);
	
	void UnloadScenes(List<String> sceneNames);

	void RenderScenesUI();
	void RenderScenesMeshes();
	void UpdateScenes(float deltaTime);

private:
	List<AScene*> m_ActiveScenes;
	List<AScene*> m_LoadedScenes;
	HashTable<String, AScene*> m_SceneTable;

	Camera* m_Camera;

	AScene* GetSceneOfName(StringRef sceneName);
	bool IsSceneRegistered(StringRef sceneName);
	bool IsSceneLoaded(StringRef sceneName);
	bool IsSceneActive(StringRef sceneName);
};
