#pragma once
#include "AssetManagement/Asset.h"
#include "RenderSystem/Mesh.h"

class Model final : public Asset
{
public:
	Model(StringRef name,
		  StringRef filepath);
	~Model() override;
	MAKE_ASSET(Model)

	Mesh& GetMesh();
private:
	Mesh* m_MeshData;
};
