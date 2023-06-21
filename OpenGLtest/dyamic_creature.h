#pragma once
#include "dynamic.h"
#include "texture.h"
#include "main_vertex_bufer.h"

class dynamicCreature : public dynamic
{
public:
	dynamicCreature(std::string name, texture* textura);

	int getHealth();
	int getMaxHealth();
	void setHealth(int health);
	void setMaxHealth(int maxHealth);

	void setVel(float x, float y);

	float getTexturePosX() const override;
	float getTexturePosY() const override;
	static float textureStepX;
	static float textureStepY;

protected:
	enum { SOUTH = 0, WEST = 1, NORTH = 2, EAST = 3 } facingDirection;
	enum { STANDING, WALKING, CELEBRATING ,DEAD} graphicState;
	float timer;
	int graphicCounter;

private:
	int health;
	int maxHealth;

public:
	void update(float fElapsedTime) override;
};

