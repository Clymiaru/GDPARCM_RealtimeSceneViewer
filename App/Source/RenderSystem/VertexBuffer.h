#pragma once

#include "glad.h"

class VertexBuffer final
{
public:
	VertexBuffer();
	explicit VertexBuffer(GLuint size);
	VertexBuffer(float* vertices, GLuint size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void SetData(const void* data, GLuint size) const;
private:
	GLuint m_ID;
};