#pragma once
#include "RenderSystem/Camera.h"

#include "Utils/TypeAlias.h"

class AScene
{
public:
	explicit AScene(StringRef name);
	virtual ~AScene() = default;

	void Load();
	void Unload();

	virtual void RenderMeshes() = 0;
	virtual void RenderUI() = 0;
	
	StringRef GetName() const;
private:
	// TODO: Ask how to determine how to load the resources
	// Most friendly way would be to store the filenames in the file
	// and read that to determine the resources to load
	
	// Another way is to just hardcode the resources to load

	// Idea:
	// We can have a manager to store all meshes
	// So that any meshes that are common would not need to be loaded anymore
	
	virtual void LoadResources() = 0;
	virtual void UnloadResources() = 0;

	String m_Name;

protected:
	Camera* m_Camera;
};
