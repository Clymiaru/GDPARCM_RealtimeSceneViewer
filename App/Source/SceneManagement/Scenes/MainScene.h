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
                               const glm::vec2& size,
                               std::function<void()> onView);

	bool AreAllScenesLoaded();

	void ViewAllScenes();

	float m_Progress;

	std::array<bool, 5> m_ActiveScenes = {true, false, false, false, false};
};
