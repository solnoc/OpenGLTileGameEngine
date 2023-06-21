#pragma once
#include "dyamic_creature.h"
#include "text_manager.h"

class command 
{
public:
	command();

	virtual void Start() = 0;
	virtual void Update(float fElapsedTime) = 0;

	bool Completed;
	bool Started;
};

class move_command : public command
{
public:
	move_command(dynamicCreature* creature, float destinationX, float destinationY, float duration);
	~move_command();

	void Start() override;
	void Update(float fElapsedTime) override;

private:
	dynamicCreature* creature;
	float destinationX;
	float destinationY;
	float duration;
	float timer;
	float startX;
	float startY;
};

class display_text : public command
{
public:
	display_text(textManager* managerText, bool dispaly);

	void Start() override;
	void Update(float fElapsedTime) override;

private:
	bool display;
	textManager* managerText;
};
