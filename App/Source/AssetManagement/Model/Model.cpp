#include "pch.h"
#include "Model.h"

Model::Model(StringRef name,
	         StringRef filepath,
	         StringRef basePath,
	         Shader& shader,
			 StringRef sceneOwner) :
	Asset{name, filepath},
	m_SceneOwner{sceneOwner},
	m_MeshData{nullptr}
{
	m_MeshData = Mesh::Load(basePath, name, shader);
}

Model::~Model()
{
}

Mesh& Model::GetMesh() const
{
	return *m_MeshData;
}
