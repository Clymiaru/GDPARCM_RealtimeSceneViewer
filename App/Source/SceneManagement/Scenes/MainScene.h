#pragma once
#include <array>
#include <functional>

#include <glm/vec2.hpp>

#include "SceneManagement/AScene.h"

class MainScene final : public AScene
{
public:
	MainScene();
	~MainScene() override;

	void RenderMeshes() override;
	void RenderUI() override;

private:
	void LoadResources() override;
	void UnloadResources() override;

	void CreateViewAllButton(const glm::vec2& size,
							 float spacing);

	void CreateSceneButtons(int amountOfScenes,
						   const glm::vec2& size,
						   float xSpacing);

	void CreateUnloadSceneButton(int sceneID,
							     const glm::vec2& size,
							     std::function<void()> onUnload);

	void CreateViewSceneButton(int sceneID,
                               const glm::vec2& size);

	void CreatePerSceneLoadingBar(int sceneID,
								  const glm::vec2& size);

	void CreateAllSceneLoadingBar(const glm::vec2& size);

	void CreateLoadSceneButton(int sceneID,
                               const glm::vec2& size,
                               std::function<void()> onLoad);

	bool AreAllScenesLoaded();

	void ViewAllScenes();

	void ViewScene(int sceneID);

	float m_Progress;
	float m_Ticks = 0;

	std::array<float, 5> m_LoadingProgress = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	std::array<bool, 5> m_ActiveScenes = {false, false, false, false, false};
	std::array<bool, 5> m_ScenesLoaded = {true, true, true, true, true};
	bool m_ViewAllScenes = false;
};
