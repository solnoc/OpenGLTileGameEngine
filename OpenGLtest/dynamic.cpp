#include "dynamic.h"

dynamic::dynamic(std::string name)
{
	this->name = name;
	this->posX = 0.0f;
	this->posY = 0.0f;
	this->velX = 0.0f;
	this->velY = 0.0f;
	this->solidVsDynamic = true;
	this->solidVsStatic = true;
	this->friendly = true;
}

void dynamic::setPos(float x, float y)
{
	this->posX = x;
	this->posY = y;
}
float dynamic::getPosX() const
{
	return this->posX;
}
float dynamic::getPosY() const
{
	return this->posY;
}
float dynamic::getVelX() const
{
	return this->velX;
}
float dynamic::getVelY() const
{
	return this->velY;
}


float dynamic::getTexturePosX() const
{
	return 0.0f;
}
float dynamic::getTexturePosY() const
{
	return 0.0f;
}
void dynamic::setTexture(texture* textura)
{
	this->textura = textura;
}
texture* dynamic::getTexture()
{
	return this->textura;
}