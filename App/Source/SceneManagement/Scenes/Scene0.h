#pragma once
#include "SceneManagement/AScene.h"

#include <glm/vec2.hpp>
#include "RenderSystem/Mesh.h"
#include "RenderSystem/Shader.h"

struct DebugData0
{
	glm::vec3 CameraPosition;
	glm::vec3 CameraRotation;

};

class Scene0 final : public AScene
{
public:
	Scene0();
	~Scene0() override;
		
	void RenderUI(Camera& camera) override;
	void RenderMeshes(Camera& camera) override;
	void Update(float deltaTime) override;
	int GetMaxAssets() override;

private:
	void LoadResources() override;
	void UnloadResources() override;

	Shader* shader = nullptr;
	bool m_AssetsLoaded = false;
	int const maxAssets = 3;
};
