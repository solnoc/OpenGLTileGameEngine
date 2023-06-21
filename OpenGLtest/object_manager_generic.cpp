#pragma once
#include "object_manager_generic.h"

void objectManagerGeneric::update(float fElapsedTime)
{
	this->updateData();
	this->updateGpuData();
}

void objectManagerGeneric::updateGpuData()
{
	this->m_vertexBuffer->updateBuffer(this->bufferData, this->bufferDataSize * sizeof(float));
}

objectManagerGeneric::objectManagerGeneric(Camera* camera)
{
	this->camera = camera;
}
