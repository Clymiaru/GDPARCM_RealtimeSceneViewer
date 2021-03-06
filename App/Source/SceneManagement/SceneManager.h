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

	void ActivateScenes();
	void DeactivateScenes();

	void MarkScenesToActivate(List<String> sceneNames);
	void MarkScenesToDeactivate(List<String> sceneNames);
	
	void UnloadScenes(List<String> sceneNames);

	int GetMaxAssetOfScene(StringRef sceneName);

	void RenderScenesUI();
	void RenderScenesMeshes();
	void UpdateScenes(float deltaTime);

private:
	List<AScene*> m_ActiveScenes;
	List<AScene*> m_LoadedScenes;
	HashTable<String, AScene*> m_SceneTable;

	Queue<AScene*> m_ActivateSceneQueue;
	Queue<AScene*> m_DeactivateSceneQueue;
	
	Camera* m_Camera;

	AScene* GetSceneOfName(StringRef sceneName);
	bool IsSceneRegistered(StringRef sceneName);
	bool IsSceneLoaded(StringRef sceneName);
	bool IsSceneActive(StringRef sceneName);
};
