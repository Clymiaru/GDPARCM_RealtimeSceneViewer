#pragma once
#include "SceneManagement/AScene.h"

#include <glm/vec2.hpp>
#include "RenderSystem/Mesh.h"
#include "RenderSystem/Shader.h"


class FirstScene final : public AScene
{
public:
	FirstScene();
	~FirstScene() override;
		
	void RenderUI(Camera& camera) override;
	void RenderMeshes(Camera& camera) override;
	void Update(float deltaTime) override;

private:
	void LoadResources() override;
	void UnloadResources() override;
	
	Mesh* mesh = nullptr;
	Shader* shader = nullptr;
};

