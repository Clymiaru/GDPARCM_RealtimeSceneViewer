#pragma once

#include "glad.h"

class VertexArray final
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
private:
	GLuint m_ID;
};