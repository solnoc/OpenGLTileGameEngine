#include "command.h"

command::command()
{
	Completed = false;
}

move_command::move_command(dynamicCreature* creature, float destinationX, float destinationY, float duration)
{
	this->creature = creature;
	this->destinationX = destinationX;
	this->destinationY = destinationY;
	this->duration = std::max(duration, 0.001f);
	this->timer = 0;
	this->startX = creature->getPosX();
	this->startY = creature->getPosY();
	this->Started = false;
}

move_command::~move_command()
{

}

void move_command::Start()
{
	startX = creature->getPosX();
	startY = creature->getPosY();
}

void move_command::Update(float fElapsedTime)
{
	this->timer += fElapsedTime;
	float t = this->timer / this->duration;
	if (t > 1.0f)
	{
		t = 1.0f;
	}

	float x = this->startX + (this->destinationX - this->startX) * t;
	float y = this->startY + (this->destinationY - this->startY) * t;

	this->creature->setPos(x, y);

	float vx = (this->destinationX - this->startX) / this->duration;
	float vy = (this->destinationY - this->startY) / this->duration;

	this->creature->setVel(vx, vy);

	if (this->timer >= this->duration)
	{
		this->Completed = true;
		this->creature->setVel(0, 0);
		this->creature->setPos(this->destinationX, this->destinationY);
	}
}

display_text::display_text(textManager* managerText, bool display)
{
	this->Started = false;
	this->managerText = managerText;
	this->display = display;
}

void display_text::Start()
{
	this->Started = true;
}

void display_text::Update(float fElapsedTime)
{
	this->managerText->displayText = this->display;
	this->Completed = true;
}