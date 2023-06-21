#pragma once
#include <string>
#include "texture.h"

class dynamic
{
public:
	dynamic(std::string name);

	float getPosX() const;
	float getPosY() const;
	float getVelX() const;
	float getVelY() const;

	void setPos(float x, float y);

	virtual float getTexturePosX() const;
	virtual float getTexturePosY() const;
	void setTexture(texture* textura);
	texture* getTexture();

protected:
	float posX;
	float posY;
	float velX;
	float velY;
	bool solidVsStatic;
	bool solidVsDynamic;
	bool friendly;
	std::string name;

	texture* textura;

public:
	virtual void updateSelfInBuffer(float ox, float oy) {}
	virtual void update(float fElapsedTime) {}
};

