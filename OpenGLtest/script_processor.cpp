#include "script_processor.h"

scriptProcessor::scriptProcessor()
{
	this->controlGiven = true;
}

scriptProcessor::~scriptProcessor()
{
	for (int i = 0; i < this->commands.size(); i++)
	{
		delete this->commands[i];
	}
}

void scriptProcessor::addCommand(command* cmd)
{
	this->commands.push_back(cmd);
}

void scriptProcessor::updateCurrentCommand(float fElapsedTime)
{
	if (this->commands.size() > 0)
	{
		this->controlGiven = false;
		if (!this->commands[0]->Completed)
		{
			if (!this->commands[0]->Started)
			{
				this->commands[0]->Start();
				this->commands[0]->Started = true;
			}
			else
			{
				this->commands[0]->Update(fElapsedTime);
			}
		}
		else
		{
			delete this->commands[0];
			this->commands.erase(this->commands.begin());
		}
	}
	else
	{
		this->controlGiven = true;
	}
}

void scriptProcessor::Clean()
{
	while (this->commands.size() > 0)
	{
		if (this->commands[0]->Completed)
		{
			delete this->commands[0];
			this->commands.erase(this->commands.begin());
		}
		else
		{
			break;
		}
	}
}