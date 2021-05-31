#pragma once
#include "Utils/Log.h"
#include "Utils/TypeAlias.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include "Camera.h"
#include "Utils/Transform.h"
#include "RenderSystem/IndexBuffer.h"
#include "RenderSystem/VertexArray.h"
#include "RenderSystem/VertexBuffer.h"
#include "Shader.h"

#include "AssetManagement/Model/Model.h"


class Mesh final
{
public:
	Mesh();
	~Mesh();

	Mesh(Model& modelData,
		 Shader& shader);

	void Draw(const Camera& camera) const;

	Transform& GetTransform();

protected:
	VertexArray* m_VAO;
	VertexBuffer* m_PositionBuffer;
	IndexBuffer* m_ElementBuffer;
	Shader* m_Shader;

	std::vector<float> m_Positions;
	std::vector<GLuint> m_Indices;

	Transform m_Transform;
};
