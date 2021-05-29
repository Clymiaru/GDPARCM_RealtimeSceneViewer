#pragma once
#include "SceneManagement/AScene.h"

class Scene2 final : public AScene
{
public:
	Scene2();
	~Scene2() override;
		
	void RenderUI() override;
	void RenderMeshes() override;

private:
	void LoadResources() override;
	void UnloadResources() override;
};
