#pragma once

#include "Utils/TypeAlias.h"

class AScene
{
public:
	explicit AScene(StringRef name);
	virtual ~AScene() = default;

	void LoadResources();
	virtual void LoadResourcesImpl() = 0;
	virtual void CreateEntities() = 0;

	virtual void Initialize() = 0;
	virtual void Deinitialize() = 0;
	
	virtual void DestroyEntities() = 0;
	virtual void UnloadResources() = 0;
	
	StringRef GetName() const;
private:
	String m_Name;
};
