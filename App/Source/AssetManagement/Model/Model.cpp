#include "pch.h"
#include "Model.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "Utils/Log.h"

Model::Model(StringRef name,
             StringRef filepath,
             StringRef basePath) :
	Asset{name, filepath}
{
	String err;
	
	const String objFilename = name + ".obj";
	const String objFilepath = filepath;

	List<tinyobj::shape_t> shapes;
	List<tinyobj::material_t> materials;

	tinyobj::LoadObj(shapes,
                     materials,
                     err,
                     objFilepath.c_str(),
                     basePath.c_str());

	if (!err.empty())
	{
		LOG(err.c_str());
	}

//	LOG("Successfully Loaded Mesh: " << objFilepath.c_str());

	m_Vertices = std::move(shapes.front().mesh.positions);
	m_Indices = std::move(shapes.front().mesh.indices);
}

Model::~Model()
{
}

List<float>& Model::GetVertices()
{
	return m_Vertices;
}

List<GLuint>& Model::GetIndices()
{
	return m_Indices;
}