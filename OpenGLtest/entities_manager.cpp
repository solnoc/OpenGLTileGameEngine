#pragma once

#include "entities_manager.h"

void entitiesManager::addEntity(dynamic* entity)
{
	this->entities.push_back(entity);
}
void entitiesManager::removeEntity(dynamic* entity)
{
	for (int i = 0; i < this->entities.size(); i++)
	{
		if (this->entities[i] == entity)
		{
			this->entities.erase(this->entities.begin() + i);
			return;
		}
	}
}
void entitiesManager::removeEntity(int id)
{
	this->entities.erase(this->entities.begin() + id);
}
dynamic* entitiesManager::getEntity(int id)
{
	return this->entities[id];
}

inline bool entitiesManager::isVisible(int x, int y)
{
	return (x >= this->camera->CameraX() && x < this->camera->CameraX() + this->camera->VisibleTilesX() + this->camera->ExtraTilesToDrawX()
		&& y >= this->camera->CameraY() && y < this->camera->CameraY() + this->camera->VisibleTilesY() + this->camera->ExtraTilesToDrawY());
}

void entitiesManager::updateEntities(float fElapsedTime)
{
	for (int i = 0; i < this->entities.size(); i++)
	{
		this->entities[i]->update(fElapsedTime);

		float playerPosX = this->entities[i]->getPosX();
		float playerPosY = this->entities[i]->getPosY();

		float playerVelX = this->entities[i]->getVelX() * fElapsedTime;
		float playerVelY = this->entities[i]->getVelY() * fElapsedTime;

		float newPlayerPosX = playerPosX + playerVelX;
		float newPlayerPosY = playerPosY + playerVelY;

		if (playerVelX < 0.0f)
		{
			if (currentMap->getSolid(newPlayerPosY, playerPosX) || currentMap->getSolid(playerPosY + 0.9f, newPlayerPosX))
			{
				newPlayerPosX = (int)newPlayerPosX + 1;
				playerVelX = 0.0f;
			}
		}
		else
		{
			if (currentMap->getSolid(playerPosY, newPlayerPosX + 1.0f) || currentMap->getSolid(playerPosY + 0.9f, newPlayerPosX + 1.0f))
			{
				newPlayerPosX = (int)newPlayerPosX;
				playerVelX = 0.0f;
			}
		}
		if (playerVelY < 0.0f)
		{
			if (currentMap->getSolid(newPlayerPosY, playerPosX) || currentMap->getSolid(newPlayerPosY, playerPosX + 0.9f))
			{
				newPlayerPosY = (int)newPlayerPosY + 1;
				playerVelY = 0.0f;
			}
		}
		else
		{
			if (currentMap->getSolid(newPlayerPosY + 1.0f, playerPosX) || currentMap->getSolid(newPlayerPosY + 1.0f, playerPosX + 0.9f))
			{
				newPlayerPosY = (int)newPlayerPosY;
				playerVelY = 0.0f;
			}
		}

		for (int j = 0; j < this->entities.size(); j++)
		{
			if (i != j)
			{
				if (newPlayerPosX >= this->entities[j]->getPosX() && newPlayerPosX < this->entities[j]->getPosX() + 1.0f
					&& newPlayerPosY >= this->entities[j]->getPosY() && newPlayerPosY < this->entities[j]->getPosY() + 1.0f)
				{
					newPlayerPosX = playerPosX;
					newPlayerPosY = playerPosY;
					playerVelX = 0.0f;
					playerVelY = 0.0f;
				}
			}
		}

		this->entities[i]->setPos(newPlayerPosX, newPlayerPosY);

	}
}

void entitiesManager::updateData()
{
	int i = this->drawCount;
	while(i < this->entities.size() && !(this->isVisible(this->entities[i]->getPosX(), this->entities[i]->getPosY())))
	{
		i++;
	}
	if (i < this->entities.size())
	{
		((float*)this->bufferData)[0] = (((this->entities[i]->getPosX() - this->camera->CameraX()) * this->camera->TileWidth()) - (this->camera->ScreenWidth() / 2.0f) - this->camera->OffsetX()) / (float)(this->camera->ScreenWidth() / 2.0f);
		((float*)this->bufferData)[1] = (((this->entities[i]->getPosY() - this->camera->CameraY()) * this->camera->TileHeight()) - (this->camera->ScreenHeight() / 2.0f) - this->camera->OffsetY()) / (float)(this->camera->ScreenHeight() / 2.0f);
		((float*)this->bufferData)[2] = this->entities[i]->getTexturePosX();
		((float*)this->bufferData)[3] = this->entities[i]->getTexturePosY();

		((float*)this->bufferData)[4] = ((float*)this->bufferData)[0];
		((float*)this->bufferData)[5] = (((this->entities[i]->getPosY() - this->camera->CameraY()) * this->camera->TileHeight()) - (this->camera->ScreenHeight() / 2.0f) - this->camera->OffsetY() + this->camera->TileHeight()) / (float)(this->camera->ScreenHeight() / 2.0f);
		((float*)this->bufferData)[6] = this->entities[i]->getTexturePosX();
		((float*)this->bufferData)[7] = this->entities[i]->getTexturePosY() + 0.33f;

		((float*)this->bufferData)[8] = (((this->entities[i]->getPosX() - this->camera->CameraX()) * this->camera->TileWidth()) - (this->camera->ScreenWidth() / 2.0f) - this->camera->OffsetX() + this->camera->TileWidth()) / (float)(this->camera->ScreenWidth() / 2.0f);
		((float*)this->bufferData)[9] = (((this->entities[i]->getPosY() - this->camera->CameraY()) * this->camera->TileHeight()) - (this->camera->ScreenHeight() / 2.0f) - this->camera->OffsetY() + this->camera->TileHeight()) / (float)(this->camera->ScreenHeight() / 2.0f);
		((float*)this->bufferData)[10] = this->entities[i]->getTexturePosX() + 0.2f;
		((float*)this->bufferData)[11] = this->entities[i]->getTexturePosY() + 0.33f;

		((float*)this->bufferData)[12] = (((this->entities[i]->getPosX() - this->camera->CameraX()) * this->camera->TileWidth()) - (this->camera->ScreenWidth() / 2.0f) - this->camera->OffsetX() + this->camera->TileWidth()) / (float)(this->camera->ScreenWidth() / 2.0f);
		((float*)this->bufferData)[13] = ((float*)this->bufferData)[1];
		((float*)this->bufferData)[14] = this->entities[i]->getTexturePosX() + 0.2f;
		((float*)this->bufferData)[15] = this->entities[i]->getTexturePosY();

		this->m_vertexBuffer->updateBuffer(this->bufferData, 16 * sizeof(float));
	}
	this->drawCount = i + 1;
}

void entitiesManager::update(float fElapsedTime)
{
	this->updateEntities(fElapsedTime);
}
void entitiesManager::draw()
{
	this->drawCount = 0;
	while (this->drawCount < this->entities.size())
	{
		this->updateData();

		if(this->drawCount > this->entities.size())
			return;

		this->entities[this->drawCount - 1]->getTexture()->Bind();

		this->m_shader->Bind();
		this->m_shader->setUniform1i("u_Texture", 0);

		this->m_renderer->Draw(*this->m_vertexArray, *this->m_indexBuffer, *this->m_shader);
	}
}

void entitiesManager::setCurrentMap(gameMap* map)
{
	this->currentMap = map;
}

entitiesManager::entitiesManager(Camera* camera)
	:objectManagerGeneric(camera)
{
	this->drawCount = 0;

	this->bufferDataSize = 16;
	this->indecesCount = 6;

	this->bufferData = new float[this->bufferDataSize];
	this->indeces = new unsigned int[this->indecesCount];

	this->indeces[0] = 0;
	this->indeces[1] = 1;
	this->indeces[2] = 2;
	this->indeces[3] = 2;
	this->indeces[4] = 3;
	this->indeces[5] = 0;

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
entitiesManager::~entitiesManager()
{
	delete this->m_renderer;
	delete this->m_shader;
	delete this->m_vertexArray;
	delete this->m_indexBuffer;
	delete this->m_vertexBufferLayout;
	delete this->m_vertexBuffer;

	delete[] this->indeces;
	delete[] this->bufferData;
}