#pragma once
#include <array>

#include <glm/vec2.hpp>
#include "RenderSystem/Mesh.h"
#include "RenderSystem/Shader.h"

#include "SceneManagement/AScene.h"

struct DebugData
{
	glm::vec3 CameraPosition;
	glm::vec3 CameraRotation;

	DebugData() :
		CameraPosition{0.0f},
		CameraRotation{0.0f}
	{
	}
};

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

	void CreateDebugWindow();
	void SetDebugRespectiveAttributes() const;

	void CreateViewAllButton(const glm::vec2& size,
							 float spacing);

	void CreateSceneButtons(int amountOfScenes,
						   const glm::vec2& size,
						   float xSpacing);

	void CreateUnloadSceneButton(int sceneID,
							     const glm::vec2& size);

	void CreateViewSceneButton(int sceneID,
                               const glm::vec2& size);

	void CreatePerSceneLoadingBar(int sceneID,
								  const glm::vec2& size);

	void CreateAllSceneLoadingBar(const glm::vec2& size) const;

	void ViewAllScenes();

	void ViewScene(int sceneID);
	void LoadScene(int sceneID);
	void UnloadScene(int sceneID);

	float m_Ticks = 0;

	DebugData m_DebugData;

	Mesh* mesh = nullptr;
	Shader* shader = nullptr;

	std::array<float, 5> m_LoadingProgress = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	std::array<bool, 5> m_ActiveScenes = {false, false, false, false, false};
	std::array<bool, 5> m_ScenesLoaded = {true, true, true, true, true};
	bool m_ViewAllScenes = false;
};
