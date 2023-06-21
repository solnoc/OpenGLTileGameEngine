#pragma once
#include "command.h"
#include <vector>

class scriptProcessor
{
private:
	std::vector<command*> commands;

public:
	scriptProcessor();
	~scriptProcessor();

	void addCommand(command* cmd);
	void updateCurrentCommand(float fElapsedTime);
	void Clean();

	bool controlGiven;

};