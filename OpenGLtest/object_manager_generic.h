#pragma once

#include "vertex_array.h"
#include "vertex_buffer_layout.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "shader.h"
#include "renderer.h"
#include "camera.h"


class objectManagerGeneric
{
protected:
	Camera* camera;

public:
	virtual void update(float fElapsedTime);
	virtual void draw() = 0;

	objectManagerGeneric(Camera* camera);
protected:
	void* bufferData;
	long bufferDataSize;
	unsigned int* indeces;
	unsigned int indecesCount;

protected:
	vertexBuffer* m_vertexBuffer;
	vertexBufferLayout* m_vertexBufferLayout;
	indexBuffer* m_indexBuffer;
	vertexArray* m_vertexArray;
	shader* m_shader;
	renderer* m_renderer;

	virtual void updateData() = 0;
	virtual void updateGpuData();

};