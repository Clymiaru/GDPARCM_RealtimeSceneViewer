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
		
	void RenderUI() override;
	void RenderMeshes() override;

private:
	void LoadResources() override;
	void UnloadResources() override;

	Mesh* mesh = nullptr;
	Shader* shader = nullptr;
};
