#pragma once
#include "SceneManagement/AScene.h"

#include <glm/vec2.hpp>
#include "RenderSystem/Mesh.h"
#include "RenderSystem/Shader.h"

class Scene3 final : public AScene
{
public:
	Scene3();
	~Scene3() override;
		
	void RenderUI(Camera& camera) override;
	void RenderMeshes(Camera& camera) override;
	void Update(float deltaTime) override;


private:
	void LoadResources() override;
	void UnloadResources() override;

	Mesh* mesh = nullptr;
	Shader* shader = nullptr;
};
