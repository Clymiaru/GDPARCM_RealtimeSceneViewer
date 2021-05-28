#pragma once

#include "glad.h"

class IndexBuffer final
{
public:
	IndexBuffer();
	IndexBuffer(GLuint* indices, GLuint count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	GLuint GetCount() const;
private:
	GLuint m_Count;
	GLuint m_ID;
};
