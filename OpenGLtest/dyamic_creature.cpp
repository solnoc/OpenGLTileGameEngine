#include "dyamic_creature.h"

dynamicCreature::dynamicCreature(std::string name, texture* textura)
	:dynamic(name)
{
	this->setTexture(textura);
	this->health = 10;
	this->maxHealth = 10;
	this->facingDirection = SOUTH;
	this->graphicState = STANDING;
	this->timer = 0;
	this->graphicCounter = 0;
}
void dynamicCreature::setVel(float x, float y)
{
	this->velX = x;
	this->velY = y;
}
void dynamicCreature::update(float fElapsedTime)
{
	this->timer += fElapsedTime;
	if (this->timer > 0.2f)
	{
		this->timer -= 0.2f;
		this->graphicCounter++;
		this->graphicCounter %= 3;
	}

	if (this->getVelX() != 0.0f || this->getVelY() != 0.0f)
		this->graphicState = WALKING;
	else
		this->graphicState = STANDING;

	if (this->health <= 0)
		this->graphicState = DEAD;

	if (this->getVelX() > 0.0f)
		this->facingDirection = EAST;
	else if (this->getVelX() < 0.0f)
		this->facingDirection = WEST;
	if (this->getVelY() < 0.0f)
		this->facingDirection = SOUTH;
	else if (this->getVelY() > 0.0f)
		this->facingDirection = NORTH;
}
int dynamicCreature::getHealth()
{
	return this->health;
}
int dynamicCreature::getMaxHealth()
{
	return this->maxHealth;
}
void dynamicCreature::setHealth(int health)
{
	this->health = health;
}
void dynamicCreature::setMaxHealth(int maxHealth)
{
	this->maxHealth = maxHealth;
}

float dynamicCreature::getTexturePosX() const
{
	if (this->graphicState == STANDING)
	{
		return 0.6f;
	}
	else if (this->graphicState == CELEBRATING)
	{
		return 0.8f;
	}
	else if (this->graphicState == DEAD)
	{
		return 0.8f;
	}
	else if (this->facingDirection == SOUTH)
	{
		return 0.0f;
	}
	else if (this->facingDirection == WEST)
	{
		return 0.2f;
	}
	else if (this->facingDirection == NORTH)
	{
		return 0.4f;
	}
	else
	{
		return 0.6f;
	}

	return -1.0f;
}
float dynamicCreature::getTexturePosY() const
{
	if (this->graphicState == STANDING)
	{
		return 0.66f;
	}
	else if (this->graphicState == CELEBRATING)
	{
		return 0.33f;
	}
	else if (this->graphicState == DEAD)
	{
		return 0.0f;
	}
	else
	{
		if (this->graphicCounter == 0)
			return 0.0f;
		else if (this->graphicCounter == 1)
			return 0.33f;
		else
			return 0.66f;
	}
	return -1.0f;
}