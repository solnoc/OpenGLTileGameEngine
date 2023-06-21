#include "singleton_assets.h"

singletonAssets::singletonAssets()
{
}
singletonAssets& singletonAssets::get()
{
	static singletonAssets original;
	return original;
}
texture* singletonAssets::getTexture(std::string name)
{
	return this->texturi[name];
}
void singletonAssets::loadTextures()
{
	auto load = [&](std::string name, std::string filepath)
	{
		texture* textura = new texture(filepath);
		this->texturi[name] = textura;
	};

	load("city", "city_and_inside.png");
	load("forest", "forest.png");
	load("characther", "Lamar1.png");
	load("hello_my_ni", "hello_my_ni.png");
}
