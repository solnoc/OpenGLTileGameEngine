#pragma once
#include "map_manager.h"

gameMap* mapManager::getCurrentMap() const
{
	return this->currentMap;
}

void mapManager::draw()
{
	this->m_renderer->Clear();

	this->currentMap->getTexture()->Bind();
	this->m_shader->Bind();
	this->m_shader->setUniform1i("u_Texture", 0);
	this->m_renderer->Draw(*this->m_vertexArray, *this->m_indexBuffer, *this->m_shader);
}

void mapManager::setCurrentMap(gameMap* currentMap, int spawnTileX, int spawnTileY, float offsetX, float offsetY)
{
	if (this->currentMap != nullptr)
		delete this->currentMap;
	this->currentMap = currentMap;

	this->mapWidth = currentMap->getWidth();
	this->mapHeight = currentMap->getHeight();

	if (spawnTileX < 0 || spawnTileX >= this->mapWidth) throw("When changing map in map manager, spawnTileX is out of the boundarys of the map.");
	if (spawnTileY < 0 || spawnTileY >= this->mapHeight) throw("When changing map in map manager, spawnTileY is out of the boundarys of the map.");

	if (offsetX < 0.0f || offsetX >= 1.0f) throw("When changing map in map manager, offsetX is not between [0.0f,1.0f)");
	if (offsetY < 0.0f || offsetY >= 1.0f) throw("When changing map in map manager, offsetY is not between [0.0f,1.0f)");

	auto getVisible = [&](int spawnPos, int visible, int mapSize)
	{
		if (spawnPos < visible / 2)
		{
			return 0;
		}
		else if (spawnPos >= mapSize - visible)
		{
			return mapSize - visible - 1;
		}
		return spawnPos;
	};
	this->camera->setCamera(getVisible(spawnTileX, this->camera->VisibleTilesX(), this->mapWidth),
							getVisible(spawnTileY, this->camera->VisibleTilesY(), this->mapHeight), 
							offsetX, offsetY);
	this->camera->setScreenBounds(this->currentMap->getWidth(), this->currentMap->getHeight());
}
void mapManager::updateData()
{
	int texTilesX = this->currentMap->getTexture()->getWidth() / this->camera->TileWidth();
	int texTilesY = this->currentMap->getTexture()->getHeight() / this->camera->TileHeight();

	float textSizeNormalizedX = 1.0f / texTilesX;
	float textSizeNormalizedY = 1.0f / texTilesY;

	for (int i = 0; i < this->camera->VisibleTilesY() + this->camera->ExtraTilesToDrawY(); i++)
	{
		for (int j = 0; j < this->camera->VisibleTilesX() + this->camera->ExtraTilesToDrawX(); j++)
		{
			int textureIndex = this->currentMap->getIndex(i + this->camera->CameraY(), j + this->camera->CameraX());
			textureIndex--;
			float normalizedTextureOffsetOnX = (textureIndex % texTilesX) * textSizeNormalizedX;
			float normalizedTextureOffsetOnY = ((texTilesY-1) - (textureIndex / texTilesX)) * textSizeNormalizedY;
			int dataBufferIndex = ((this->camera->VisibleTilesX() + this->camera->ExtraTilesToDrawX()) * i + j) * 16;
			for (int q = 0; q < 4; q++)
			{
				((float*)this->bufferData)[dataBufferIndex + q * 4] = ((j * this->camera->TileWidth()) + (q == 2 || q == 3) * this->camera->TileWidth() - (this->camera->ScreenWidth() / 2.0f) - this->camera->OffsetX()) / (this->camera->ScreenWidth() / 2.0f);
				((float*)this->bufferData)[dataBufferIndex + 1 + q * 4] = ((i * this->camera->TileHeight()) + (q == 1 || q == 2) * this->camera->TileHeight() - (this->camera->ScreenHeight() / 2.0f) - this->camera->OffsetY()) / (this->camera->ScreenHeight() / 2.0f);
				((float*)this->bufferData)[dataBufferIndex + 2 + q * 4] = (q == 2 || q == 3) * textSizeNormalizedX + normalizedTextureOffsetOnX;
				((float*)this->bufferData)[dataBufferIndex + 3 + q * 4] = (q == 1 || q == 2) * textSizeNormalizedY + normalizedTextureOffsetOnY;
			}
		}
	}
}
void mapManager::moveCamera(float offSetX, float offSetY)
{
	this->camera->moveCamera(offSetX, offSetY);
	/*
	if ((this->camera->CameraX() >= this->mapWidth - this->camera->VisibleTilesX() && offSetX > 0.0f) || 
		(this->camera->CameraX() + offSetX < 0))
	{
		offSetX = 0.0f;
	}
	if ((this->camera->CameraY() >= this->mapHeight - this->camera->VisibleTilesY() && offSetY > 0.0f) ||
		this->camera->CameraY() + offSetY < 0)
	{
		offSetY = 0.0f;
	}

	if (offSetX < 0.0f)
	{
		if (this->camera->CameraX() == 0)
		{
			this->camera->setCamera(0, this->camera->CameraY(), 0.0f, this->camera->OffsetY());
		}
		else
		{
			this->camera->moveCamera(offSetX, 0.0f);
		}
	}
	else if (this->offsetX >= this->camera->TileWidth())
	{
		this->offsetX -= this->camera->TileWidth();
		this->camera->CameraX()++;
		if (this->camera->CameraX() >= this->mapWidth - this->visibleTilesX)
		{
			this->camera->CameraX() = this->mapWidth - this->visibleTilesX;
			this->offsetX = 0.0f;
		}
	}
	if (this->offsetY < 0.0f)
	{
		this->offsetY += this->camera->TileHeight();
		this->camera->CameraY()--;
		if (this->camera->CameraY() < 0)
		{
			this->camera->CameraY() = 0;
			this->offsetY = 0.0f;
		}
	}
	else if (this->offsetY >= this->camera->TileHeight())
	{
		this->offsetY -= this->camera->TileHeight();
		this->camera->CameraY()++;
		if (this->camera->CameraY() >= this->mapHeight - this->camera->VisibleTilesY())
		{
			this->camera->CameraY() = this->mapHeight - this->camera->VisibleTilesY();
			this->offsetY = 0.0f;
		}
	}
	*/
}

mapManager::mapManager(Camera* camera)
	:objectManagerGeneric(camera)
{
	this->bufferDataSize = (this->camera->VisibleTilesY() + this->camera->ExtraTilesToDrawY()) * (this->camera->VisibleTilesX() + this->camera->ExtraTilesToDrawX()) * 4 * 4;
	this->indecesCount = (this->camera->VisibleTilesY() + this->camera->ExtraTilesToDrawY()) * (this->camera->VisibleTilesX() + this->camera->ExtraTilesToDrawX()) * 6;

	this->bufferData = new float[this->bufferDataSize];
	this->indeces = new unsigned int[this->indecesCount];
	for (int i = 0; i < this->camera->VisibleTilesY() + this->camera->ExtraTilesToDrawY(); i++)
	{
		for (int j = 0; j < this->camera->VisibleTilesX() + this->camera->ExtraTilesToDrawX(); j++)
		{
			int index = (i * (this->camera->VisibleTilesX() + this->camera->ExtraTilesToDrawX()) + j) * 6;
			(this->indeces)[index] = (i * (this->camera->VisibleTilesX() + this->camera->ExtraTilesToDrawX()) + j) * 4;
			(this->indeces)[index + 1] = (i * (camera->VisibleTilesX() + this->camera->ExtraTilesToDrawX()) + j) * 4 + 1;
			(this->indeces)[index + 2] = (i * (camera->VisibleTilesX() + this->camera->ExtraTilesToDrawX()) + j) * 4 + 2;

			(this->indeces)[index + 3] = (i * (camera->VisibleTilesX() + this->camera->ExtraTilesToDrawX()) + j) * 4;
			(this->indeces)[index + 4] = (i * (camera->VisibleTilesX() + this->camera->ExtraTilesToDrawX()) + j) * 4 + 3;
			(this->indeces)[index + 5] = (i * (camera->VisibleTilesX() + this->camera->ExtraTilesToDrawX()) + j) * 4 + 2;
		}
	}

	this->m_vertexBuffer = new vertexBuffer((void*)0, this->bufferDataSize * sizeof(float));

	this->m_vertexBufferLayout = new vertexBufferLayout();
	this->m_vertexBufferLayout->push<float>(2);
	this->m_vertexBufferLayout->push<float>(2);

	this->m_indexBuffer = new indexBuffer(this->indeces, this->indecesCount);

	this->m_vertexArray = new vertexArray();
	this->m_vertexArray->addBuffer(*this->m_vertexBuffer, *this->m_vertexBufferLayout);

	this->m_shader = new shader("basic.shader");

	this->m_renderer = new renderer();
}

mapManager::~mapManager()
{
	delete this->currentMap;
}
