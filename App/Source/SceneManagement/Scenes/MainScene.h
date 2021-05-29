#pragma once
#include <array>

#include <glm/vec2.hpp>
#include "RenderSystem/Mesh.h"
#include "RenderSystem/Shader.h"

#include "SceneManagement/AScene.h"

const int MAX_MESH_SCENES = 5;

enum class SceneState
{
	NotLoaded = 0,
	StartLoading = 1,
	Loaded = 2,
	Active,
	
};

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

	void RenderMeshes(Camera& camera) override;
	void RenderUI(Camera& camera) override;
	void Update(float deltaTime) override;

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

	void CreateUnloadSceneButton(int sceneID, const glm::vec2& size);

	void CreateViewSceneButton(int sceneID, const glm::vec2& size);

	void CreateLoadSceneButton(int sceneID, const glm::vec2& size);

	void CreateSceneLoadingBar(int sceneID, const glm::vec2& size);

	void CreateMainSceneLoadingBar(const glm::vec2& size) const;

	void ViewAllScenes();
	void HideAllScenes();

	void ViewScene(int sceneID);
	void LoadScene(int sceneID);
	void UnloadScene(int sceneID);

	float m_Ticks = 0;

	DebugData m_DebugData;

	Mesh* mesh = nullptr;
	Shader* shader = nullptr;

	std::array<bool, MAX_MESH_SCENES> m_ScenesStartedLoading = {true, true, true, true, true};
	std::array<float, MAX_MESH_SCENES> m_ScenesLoadingProgress = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	std::array<bool, MAX_MESH_SCENES> m_ScenesFinishedLoading = {false, false, false, false, false};

	std::array<bool, MAX_MESH_SCENES> m_ScenesActive = {false, false, false, false, false};
	bool m_ViewAllScenes = false;
};
