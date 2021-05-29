#pragma once
#include "SceneManagement/AScene.h"

#include <glm/vec2.hpp>
#include "RenderSystem/Mesh.h"
#include "RenderSystem/Shader.h"

class Scene4 final : public AScene
{
public:
	Scene4();
	~Scene4() override;
		
	void RenderUI(Camera& camera) override;
	void RenderMeshes(Camera& camera) override;
	void Update(float deltaTime) override;


private:
	void LoadResources() override;
	void UnloadResources() override;
	Mesh* mesh = nullptr;
	Shader* shader = nullptr;
};
