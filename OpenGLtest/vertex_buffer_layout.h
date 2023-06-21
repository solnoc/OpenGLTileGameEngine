#pragma once
#include <GL\glew.h>
#include <vector>
#include "error_checking.h"

struct vertexBufferLayoutElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:		   return sizeof(GLfloat);
			case GL_UNSIGNED_INT:  return sizeof(GLuint);
			case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
		}
		ASSERT(false);
		return 0;
	}
};
#include <iostream>
class vertexBufferLayout
{
private:
	std::vector<vertexBufferLayoutElement> m_elements;
	unsigned int m_stride;

public:
	vertexBufferLayout() 
		:m_stride(0){}

	template<typename T>
	void push(unsigned int count)
	{
		ASSERT(false);
	}

	template<>
	void push<float>(unsigned int count)
	{
		m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride += count * vertexBufferLayoutElement::getSizeOfType(GL_FLOAT);
	}

	template<>
	void push<unsigned int>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += count * vertexBufferLayoutElement::getSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void push<unsigned char>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += count * vertexBufferLayoutElement::getSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline unsigned int getStride() const { return m_stride; }
	inline std::vector<vertexBufferLayoutElement> getElements() const { return m_elements; }
};

