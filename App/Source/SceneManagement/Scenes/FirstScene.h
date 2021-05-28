#pragma once
#include <array>
#include <functional>

#include <glm/vec2.hpp>

#include "SceneManagement/AScene.h"

#include "RenderSystem/Mesh.h"
#include "RenderSystem/Shader.h"

class FirstScene :	public AScene
{
	public:
		FirstScene();
		~FirstScene() override;
		
		void RenderUI() override;
		void RenderMeshes() override;
		

	private:
		void LoadResources() override;
		void UnloadResources() override;
		float m_Progress;
		Mesh* mesh;
		Shader* shader;
};

