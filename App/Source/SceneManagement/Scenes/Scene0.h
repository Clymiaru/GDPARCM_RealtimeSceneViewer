#pragma once
#include "SceneManagement/AScene.h"

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
};
