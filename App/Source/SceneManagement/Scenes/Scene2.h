#pragma once
#include "SceneManagement/AScene.h"

#include <glm/vec2.hpp>
#include "RenderSystem/Mesh.h"
#include "RenderSystem/Shader.h"

class Scene2 final : public AScene
{
public:
	Scene2();
	~Scene2() override;
		
	void RenderUI(Camera& camera) override;
	void RenderMeshes(Camera& camera) override;
	void Update(float deltaTime) override;
	int GetMaxAssets() override;

private:
	void LoadResources() override;
	void UnloadResources() override;

	Mesh* mesh = nullptr;
	Shader* shader = nullptr;
	int const maxAssets = 3;

};
