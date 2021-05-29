#pragma once
#include "Utils/Log.h"
#include "Utils/TypeAlias.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include "RenderSystem/IndexBuffer.h"
#include "RenderSystem/VertexArray.h"
#include "RenderSystem/VertexBuffer.h"


#include "Shader.h"

#include "Utils/Transform.h"

class Mesh final
{
public:
	Mesh();
	~Mesh();

	Mesh(const List<float>& vertices,
         const List<GLuint>& indices,
		 Shader& shader);

	void Draw(const glm::mat4& viewProjection) const;

	static Mesh* Load(StringRef basePath,
					  StringRef filename,
					  Shader& shader);

protected:
	VertexArray* m_VAO;
	VertexBuffer* m_PositionBuffer;
	IndexBuffer* m_ElementBuffer;
	Shader* m_Shader;

	std::vector<float> m_Positions;
	std::vector<GLuint> m_Indices;

	Transform m_Transform;
};
