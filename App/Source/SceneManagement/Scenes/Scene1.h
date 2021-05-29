#pragma once
#include "SceneManagement/AScene.h"

#include <glm/vec2.hpp>
#include "RenderSystem/Mesh.h"
#include "RenderSystem/Shader.h"

class Scene1 final : public AScene
{
public:
	Scene1();
	~Scene1() override;
		
	void RenderUI(Camera& camera) override;
	void RenderMeshes(Camera& camera) override;
	void Update(float deltaTime) override;


private:
	void LoadResources() override;
	void UnloadResources() override;

	List<Mesh*> m_Meshes;
	
	Shader* shader = nullptr;
	bool m_AssetsLoaded = false;
};
