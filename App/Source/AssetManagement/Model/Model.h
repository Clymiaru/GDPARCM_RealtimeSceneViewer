#pragma once
#include "AssetManagement/Asset.h"
#include "RenderSystem/Mesh.h"

class Model final : public Asset
{
public:
	Model(StringRef name,
		  StringRef filepath,
		  StringRef basePath,
		  Shader& shader,
		  StringRef sceneOwner);
	~Model() override;
	MAKE_ASSET(Model)

	Mesh& GetMesh() const;
private:
	String m_SceneOwner;
	Mesh* m_MeshData;
};
