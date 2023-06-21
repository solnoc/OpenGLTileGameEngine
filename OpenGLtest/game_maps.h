#pragma once
#include "texture.h"
#include "vertex_array.h"

class gameMap
{
public:
	bool create(std::string filepath, texture* textura, std::string name);
	~gameMap();

private:
	int width;
	int height;
	int* indeces = nullptr;
	bool* solids = nullptr;
	std::string name;

	texture* textura;

public:
	int getWidth() const;
	void setWidth(int width);
	int getHeight() const;
	void setHeight(int height);
	std::string getName() const;
	void setName(std::string name);
	int getIndex(int i, int j) const;
	bool getSolid(int i, int j) const;
	
	texture* getTexture() const;
};

class forestMap : public gameMap
{
public:
	forestMap();

};