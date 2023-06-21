#pragma once
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class vertexArray
{
private:
	unsigned int m_rendererId;

public:
	vertexArray();
	~vertexArray();

	void addBuffer(vertexBuffer& vb, vertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;
};

