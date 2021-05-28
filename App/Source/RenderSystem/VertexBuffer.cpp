#include "pch.h"

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() :
	m_ID(0)
{
}

VertexBuffer::VertexBuffer(const GLuint size)
{
	glGenBuffers(1, &m_ID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	Unbind();
}

VertexBuffer::VertexBuffer(float* vertices,
                           const GLuint size)
{
	glGenBuffers(1, &m_ID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	Unbind();
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_ID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void* data,
                           const GLuint size) const
{
	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	Unbind();
}
