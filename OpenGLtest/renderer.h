#pragma once
#include "vertex_array.h"
#include "shader.h"
#include "index_buffer.h"

class renderer
{
public:
	void Draw(vertexArray &va, indexBuffer &ib, shader &sh);
	void Clear();
};

