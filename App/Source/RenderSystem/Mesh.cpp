#include "pch.h"
#include "Mesh.h"

#include "Core/App.h"

#include "AssetManagement/AssetManager.h"

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

Mesh::Mesh(Model& modelData,
           Shader& shader) :
	m_VAO{nullptr},
	m_PositionBuffer{nullptr},
	m_ElementBuffer{nullptr},
	m_Shader{&shader},
	m_Positions{modelData.GetVertices()},
	m_Indices{modelData.GetIndices()}
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

void Mesh::Draw(const Camera& camera) const
{
	m_Shader->Bind();
	m_VAO->Bind();
	m_Shader->SetMat4("transform", m_Transform.GetTransform());
	m_Shader->SetMat4("view_projection", camera.GetViewProjectionMatrix());
	m_ElementBuffer->Bind();
	glDrawElements(GL_TRIANGLES, m_ElementBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	m_ElementBuffer->Unbind();
	m_VAO->Unbind();
	m_Shader->Unbind();
}

Transform& Mesh::GetTransform()
{
	return m_Transform;
}