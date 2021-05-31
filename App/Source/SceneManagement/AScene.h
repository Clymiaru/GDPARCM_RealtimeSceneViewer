#pragma once
#include "RenderSystem/Camera.h"
#include "RenderSystem/Mesh.h"

#include "Utils/TypeAlias.h"

class AScene
{
public:
	explicit AScene(StringRef name);
	virtual ~AScene() = default;

	void Load();
	void Unload();
	void SetCamera(Camera& mainCamera);
	
	virtual int GetMaxAssets();
	virtual void RenderMeshes(Camera& camera) = 0;
	virtual void RenderUI(Camera& camera) = 0;
	virtual void Update(float deltaTime) = 0;
	
	StringRef GetName() const;

private:
	virtual void LoadResources() = 0;
	virtual void UnloadResources() = 0;

	String m_Name;

protected:
	Camera* m_Camera;
	List<Mesh*> m_Meshes;
	bool m_AssetsLoaded = false;
};
