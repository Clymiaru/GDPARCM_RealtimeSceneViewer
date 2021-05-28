#pragma once
#include <glm/vec2.hpp>

#include "SceneManagement/AScene.h"

class MainScene final : public AScene
{
public:
	MainScene();
	~MainScene() override;
private:
	void LoadResources() override;
	void RenderUI() override;
	void UnloadResources() override;

	void CreateViewAllButton(const glm::vec2& size,
							 float spacing);

	void CreateSceneButton(int sceneID,
						   const glm::vec2& size,
						   float xSpacing);

	float m_Progress;
};
