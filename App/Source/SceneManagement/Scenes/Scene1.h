#pragma once
#include "SceneManagement/AScene.h"

class Scene1 final : public AScene
{
public:
	Scene1();
	~Scene1() override;
		
	void RenderUI() override;
	void RenderMeshes() override;

private:
	void LoadResources() override;
	void UnloadResources() override;
};
