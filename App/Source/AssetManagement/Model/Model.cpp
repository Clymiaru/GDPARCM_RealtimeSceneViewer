#include "pch.h"
#include "Model.h"

Model::Model(StringRef name,
			 StringRef filepath) :
	Asset{name, filepath},
	m_MeshData{nullptr}
{
}

Model::~Model()
{
}

Mesh& Model::GetMesh()
{
}
