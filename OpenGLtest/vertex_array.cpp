#include "vertex_array.h"

vertexArray::vertexArray()
{
	GLCall(glGenVertexArrays(1, &m_rendererId));
}
vertexArray::~vertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_rendererId));
}
void vertexArray::addBuffer(vertexBuffer& vb, vertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
		offset += element.count * vertexBufferLayoutElement::getSizeOfType(element.type);
	}
}
void vertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_rendererId));
}
void vertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}