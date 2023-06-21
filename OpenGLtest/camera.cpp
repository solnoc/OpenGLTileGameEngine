#pragma once
#include "camera.h"
#include <iostream>

Camera::Camera(int screenWidth, int screenHeight, int tileWidth, int tileHeight, int extraTilesToDrawX, int extraTilesToDrawY, int cameraX, int cameraY, float offsetX, float offsetY)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	this->cameraX = cameraX;
	this->cameraY = cameraY;

	this->extraTilesToDrawX = extraTilesToDrawX;
	this->extraTilesToDrawY = extraTilesToDrawY;

	this->offSetX = offsetX;
	this->offSetY = offsetY;

	this->visibleTilesX = (screenWidth / tileWidth) + extraTilesToDrawX;
	this->visibleTilesY = (screenHeight / tileHeight) + extraTilesToDrawY;

	this->screenBoundX = 0;
	this->screenBoundY = 0;
}

void Camera::setScreenBounds(int ScreenBoundX, int ScreenBoundY)
{
	this->screenBoundX = ScreenBoundX;
	this->screenBoundY = ScreenBoundY;
}

void Camera::setCamera(int cameraX, int cameraY, float offSetX, float offSetY)
{
	this->cameraX = cameraX;
	this->cameraY = cameraY;
	this->offSetX = offSetX;
	this->offSetY = offSetY;

	if (this->offSetX < 0.0f)
	{
		this->cameraX += (int)(this->offSetX / this->tileWidth - 1);
		this->offSetX -= (int)(this->offSetX / this->tileWidth - 1) * this->tileWidth;
	}
	else if (this->offSetX > this->tileWidth)
	{
		this->cameraX += (int)(this->offSetX / this->tileWidth);
		this->offSetX -= (int)(this->offSetX / this->tileWidth) * this->tileWidth;
	}

	if (this->offSetY < 0.0f)
	{
		this->cameraY += (int)(this->offSetY / this->tileHeight - 1);
		this->offSetY -= (int)(this->offSetY / this->tileHeight - 1) * this->tileHeight;
	}
	else if (this->offSetY > this->tileHeight)
	{
		this->cameraY += (int)(this->offSetY / this->tileHeight);
		this->offSetY -= (int)(this->offSetY / this->tileHeight) * this->tileHeight;
	}

	clipCamera();
}

void Camera::moveCamera(float offSetX, float offSetY)
{
	this->offSetX += offSetX;
	this->offSetY += offSetY;

	if(this->offSetX < 0.0f)
	{
		this->cameraX += (int)(this->offSetX / this->tileWidth - 1);
		this->offSetX -= (int)(this->offSetX / this->tileWidth - 1) * this->tileWidth;
	}
	else if(this->offSetX > this->tileWidth)
	{
		this->cameraX += (int)(this->offSetX / this->tileWidth);
		this->offSetX -= (int)(this->offSetX / this->tileWidth) * this->tileWidth;
	}

	if (this->offSetY < 0.0f)
	{
		this->cameraY += (int)(this->offSetY / this->tileHeight - 1);
		this->offSetY -= (int)(this->offSetY / this->tileHeight - 1) * this->tileHeight;
	}
	else if (this->offSetY > this->tileHeight)
	{
		this->cameraY += (int)(this->offSetY / this->tileHeight);
		this->offSetY -= (int)(this->offSetY / this->tileHeight) * this->tileHeight;
	}

	clipCamera();
}

void Camera::clipCamera()
{
	if (this->cameraX < 0)
	{
		this->cameraX = 0;
		this->offSetX = 0.0f;
	}
	else if (this->cameraX > this->screenBoundX - this->visibleTilesX)
	{
		this->cameraX = this->screenBoundX - this->visibleTilesX;
		this->offSetX = 0.0f;
	}

	if (this->cameraY < 0)
	{
		this->cameraY = 0;
		this->offSetY = 0.0f;
	}
	else if (this->cameraY > this->screenBoundY - this->visibleTilesY)
	{
		this->cameraY = this->screenBoundY - this->visibleTilesY;
		this->offSetY = 0.0f;
	}
}

int Camera::CameraX() const
{
	return this->cameraX;
}
int Camera::CameraY() const
{
	return this->cameraY;
}

float Camera::OffsetX() const
{
	return this->offSetX;
}
float Camera::OffsetY() const
{
	return this->offSetY;
}

float Camera::ExtraTilesToDrawX() const
{
	return this->extraTilesToDrawX;
}
float Camera::ExtraTilesToDrawY() const
{
	return this->extraTilesToDrawY;
}

int Camera::VisibleTilesX() const
{
	return this->visibleTilesX;
}
int Camera::VisibleTilesY() const
{
	return this->visibleTilesY;
}

int Camera::TileWidth() const
{
	return this->tileWidth;
}
int Camera::TileHeight() const
{
	return this->tileHeight;
}

int Camera::ScreenWidth() const
{
	return this->screenWidth;
}
int Camera::ScreenHeight() const
{
	return this->screenHeight;
}

