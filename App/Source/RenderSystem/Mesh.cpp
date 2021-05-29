#include "pch.h"
#include "Mesh.h"

#include "Core/App.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

Mesh::Mesh() :
	m_VAO{nullptr},
	m_PositionBuffer{nullptr},
	m_ElementBuffer{nullptr},
	m_Shader{nullptr}
{
}

Mesh::~Mesh()
{
	delete m_ElementBuffer;
	delete m_PositionBuffer;
	delete m_VAO;
}

Mesh::Mesh(const List<float>& vertices,
           const List<GLuint>& indices,
           Shader& shader) :
	m_VAO{nullptr},
	m_PositionBuffer{nullptr},
	m_ElementBuffer{nullptr},
	m_Shader{&shader},
	m_Positions{vertices},
	m_Indices{indices}
{
	m_VAO = new VertexArray();
	m_VAO->Bind();

	m_PositionBuffer = new VertexBuffer(&m_Positions.front(),
										m_Positions.size() * sizeof(float));
	m_PositionBuffer->Bind();
	{
		const GLuint location = glGetAttribLocation(m_Shader->GetID(), "v_vertex");
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}
	m_PositionBuffer->Unbind();

	m_ElementBuffer = new IndexBuffer(&m_Indices.front(),
								  m_Indices.size());
	
	m_VAO->Unbind();
}

void Mesh::Draw(const glm::mat4& viewProjection) const
{
	m_Shader->Bind();
	m_VAO->Bind();
	m_Shader->SetMat4("transform", m_Transform.GetTransform());
	m_Shader->SetMat4("view_projection", viewProjection);
	m_ElementBuffer->Bind();
	glDrawElements(GL_TRIANGLES, m_ElementBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	m_ElementBuffer->Unbind();
	m_VAO->Unbind();
	m_Shader->Unbind();
}

Transform& Mesh::GetTransform()
{
	// TODO: insert return statement here
	return m_Transform;
}

Mesh* Mesh::Load(StringRef basePath,
				 StringRef filename,
				 Shader& shader)
{
	String err;
	const String objFilepath = basePath + filename + ".obj";

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
		//return nullptr;
	}
	
	LOG("Successfully Loaded Mesh: " << objFilepath.c_str());

	Mesh* output = new Mesh(shapes.front().mesh.positions,
	                        shapes.front().mesh.indices,
	                        shader);

	return output;
}
