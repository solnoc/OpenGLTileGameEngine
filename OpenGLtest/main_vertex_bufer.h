#pragma once
#include "vertex_buffer.h"
#include "dynamic.h"

class mainVertexBufferHandler
{
public:
	mainVertexBufferHandler(void* data, unsigned int size, int visibleX, int visibleY,int screenSizeX,int screenSizeY, int tileWidth, int tileHeight
		, int firstIndexEntities, int nrEntities);
	void modifySquareData(int i, int j, float ti, float tj, float texSize, float offsetX = 0.0f, float offsetY = 0.0f);
	int addEntity(float i, float j, float ti, float tj, float texSize);
	void addEntity(dynamic& entity);
	void modifyEntityData(float i, float j, float ti, float tj, float texSize, int entityId);
	inline int getNrEntities() const { return this->nrEntities; }
	inline vertexBuffer& getBuffer() { return this->vb; }
	inline int indexData(int i, int j) { return ((visibleX + 2) * i + j) * 16; }
	void updateData();
	inline void Bind() const { this->vb.Bind(); }
	inline void Unbind() const { this->vb.Unbind(); }

private:
	int firstIndexEntities;
	int nrEntities;
	int visibleX;
	int visibleY;
	int screenSizeX;
	int screenSizeY;
	int tileWidth;
	int tileHeight;
	vertexBuffer vb;
	void* data;
	unsigned int size;
};

