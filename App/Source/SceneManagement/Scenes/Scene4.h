#pragma once
#include "SceneManagement/AScene.h"

class Scene4 final : public AScene
{
public:
	Scene4();
	~Scene4() override;
		
	void RenderUI() override;
	void RenderMeshes() override;

private:
	void LoadResources() override;
	void UnloadResources() override;
};
