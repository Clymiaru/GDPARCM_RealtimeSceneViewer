#pragma once
#include "SceneManagement/AScene.h"

class Scene3 final : public AScene
{
public:
	Scene3();
	~Scene3() override;
		
	void RenderUI() override;
	void RenderMeshes() override;

private:
	void LoadResources() override;
	void UnloadResources() override;
};
