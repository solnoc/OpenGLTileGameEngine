#include "game_maps.h"
#include "singleton_assets.h"

#include <fstream>
#include <iostream>

bool gameMap::create(std::string filepath, texture* textura, std::string name)
{
	this->name = name;
	this->textura = textura;
	std::ifstream in(filepath);
	if (in.is_open())
	{
		in >> this->width >> this->height;
		std::cout << this->width << " " << this->height << std::endl;

		this->indeces = new int[this->width * this->height];
		this->solids = new bool[this->width * this->height];

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				in >> this->indeces[i * width + j];
				in >> this->solids[i * width + j];
			}
		}
		return true;
	}
	return false;
}
int gameMap::getIndex(int i, int j) const
{
	if (i >= 0 && i < this->height && j >= 0 && j < this->width)
	{
		return this->indeces[((this->height-1) - i) * this->width + j];
	}
	else
	{
		return 0;
	}
}
bool gameMap::getSolid(int i, int j) const
{
	if (i >= 0 && i < this->height && j >= 0 && j < this->width)
	{
		return this->solids[((this->height - 1) - i) * this->width + j];
	}
	else
	{
		return 0;
	}
}
gameMap::~gameMap()
{
	delete[] this->indeces;
	delete[] this->solids;
}

int gameMap::getWidth() const
{
	return this->width;
}
void gameMap::setWidth(int width)
{
	this->width = width;
}
int gameMap::getHeight() const
{
	return this->height;
}
void gameMap::setHeight(int height)
{
	this->height = height;
}
std::string gameMap::getName() const
{
	return this->name;
}
void gameMap::setName(std::string name)
{
	this->name = name;
}
texture* gameMap::getTexture() const
{
	return this->textura;
}

forestMap::forestMap()
{
	create("City1_encoding.txt", singletonAssets::get().getTexture("city"), "Padurea opicala");
}