#pragma once
#include "AssetManagement/Asset.h"
#include <glad.h>

class Model final : public Asset
{
public:
	Model(StringRef name,
		  StringRef filepath,
		  StringRef basePath);
	~Model() override;
	
	MAKE_ASSET(Model)

	List<float>& GetVertices();
	List<GLuint>& GetIndices();
private:
	List<float> m_Vertices;
	List<GLuint> m_Indices;
};
