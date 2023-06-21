#pragma once
#include "game_maps.h"
#include "singleton_assets.h"

#include "object_manager_generic.h"

class mapManager : public objectManagerGeneric
{
private:
	gameMap* currentMap;

	int mapWidth;
	int mapHeight;

public:
	void draw() override;

private:
	void updateData() override;

public:
	gameMap* getCurrentMap() const;
	void setCurrentMap(gameMap* currentMap, int spawnTileX = 0, int spawnTileY = 0, float offsetX = 0.0f, float offsetY = 0.0f);
	void moveCamera(float offsetX, float offsetY);
	
	mapManager(Camera* camera);
	~mapManager();
};
