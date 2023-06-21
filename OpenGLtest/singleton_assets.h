#pragma once
#include "texture.h"

#include <map>

class singletonAssets
{
public:
	static singletonAssets& get();
	singletonAssets(singletonAssets const&) = delete;
	void operator=(singletonAssets const&) = delete;

	texture* getTexture(std::string name);
	void loadTextures();
private:
	singletonAssets();
	
private:
	std::map<std::string, texture*> texturi;
};

