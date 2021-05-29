#pragma once
#include "SceneManagement/AScene.h"

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
};

