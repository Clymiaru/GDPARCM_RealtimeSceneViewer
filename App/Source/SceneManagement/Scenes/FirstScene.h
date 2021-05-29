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
		
		void RenderUI() override;
		void RenderMeshes() override;

	private:
		void LoadResources() override;
		void UnloadResources() override;


		Mesh* mesh = nullptr;
		Shader* shader = nullptr;
};

