#include "main_vertex_bufer.h"

mainVertexBufferHandler::mainVertexBufferHandler(void* data, unsigned int size, int visibleX, int visibleY, int screenSizeX, int screenSizeY, int tileWidth, int tileHeight
	, int firstIndexEntities, int nrEntities)
	:vb(data,size)
{
	this->size = size;
	this->data = data;
	this->firstIndexEntities = firstIndexEntities;
	this->nrEntities = nrEntities;
	this->visibleX = visibleX;
	this->visibleY = visibleY;
	this->screenSizeX = screenSizeX;
	this->screenSizeY = screenSizeY;
	this->tileHeight = tileHeight;
	this->tileWidth = tileWidth;
	this->nrEntities = 0;
}
void mainVertexBufferHandler::modifySquareData(int i, int j, float ti, float tj, float texSize, float offsetX, float offsetY)
{
	for (int q = 0; q < 4; q++)
	{
		int index = indexData(i, j);
		((float*)data)[index + q * 4] = ((j * tileWidth) + (q == 2 || q == 3) * tileWidth - (screenSizeX / 2.0f) + offsetX) / (screenSizeX / 2.0f);
		((float*)data)[index + 1 + q * 4] = ((i * tileHeight) + (q == 1 || q == 2) * tileHeight - (screenSizeY / 2.0f) + offsetY) / (screenSizeY / 2.0f);
		((float*)data)[index + 2 + q * 4] = (q == 2 || q == 3) * texSize + tj * texSize;
		((float*)data)[index + 3 + q * 4] = (q == 1 || q == 2) * texSize + ti * texSize;
	}
}
int mainVertexBufferHandler::addEntity(float i, float j, float ti, float tj, float texSize)
{
	for (int q = 0; q < 4; q++)
	{
		((float*)data)[firstIndexEntities + nrEntities * 16 + q * 4] = ((j * tileWidth) + (q == 2 || q == 3) * tileWidth 
																		- (screenSizeX / 2.0f)) / (screenSizeX / 2.0f);
		((float*)data)[firstIndexEntities + nrEntities * 16 + 1 + q * 4] = ((i * tileHeight) + (q == 1 || q == 2) * tileHeight
																		- (screenSizeY / 2.0f)) / (screenSizeY / 2.0f);
		((float*)data)[firstIndexEntities + nrEntities * 16 + 2 + q * 4] = (q == 2 || q == 3) * texSize + tj * texSize;
		((float*)data)[firstIndexEntities + nrEntities * 16 + 3 + q * 4] = (q == 1 || q == 2) * texSize + ti * texSize;
	}
	nrEntities++;
	return (nrEntities - 1);
}
void mainVertexBufferHandler::modifyEntityData(float i, float j, float ti, float tj, float texSize, int entityId)
{
	for (int q = 0; q < 4; q++)
	{
		((float*)data)[firstIndexEntities + entityId * 16 + q * 4] = ((j * tileWidth) + (q == 2 || q == 3) * tileWidth
			- (screenSizeX / 2.0f)) / (screenSizeX / 2.0f);
		((float*)data)[firstIndexEntities + entityId * 16 + 1 + q * 4] = ((i * tileHeight) + (q == 1 || q == 2) * tileHeight
			- (screenSizeY / 2.0f)) / (screenSizeY / 2.0f);
		((float*)data)[firstIndexEntities + entityId * 16 + 2 + q * 4] = (q == 2 || q == 3) * texSize + tj * texSize;
		((float*)data)[firstIndexEntities + entityId * 16 + 3 + q * 4] = (q == 1 || q == 2) * texSize + ti * texSize;
	}
}
void mainVertexBufferHandler::updateData()
{
	vb.Bind();
	vb.updateBuffer(data, size);
}