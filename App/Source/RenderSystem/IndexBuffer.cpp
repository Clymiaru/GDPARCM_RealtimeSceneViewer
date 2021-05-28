#include "pch.h"

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer() :
	m_Count{0},
	m_ID{0}
{
}

IndexBuffer::IndexBuffer(GLuint* indices,
                         const GLuint count) :
	m_Count(count)
{
	glGenBuffers(1, &m_ID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indices, GL_STATIC_DRAW);
	Unbind();
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_ID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint IndexBuffer::GetCount() const
{
	return m_Count;
}