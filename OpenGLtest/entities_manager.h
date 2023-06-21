#pragma once

#include "game_maps.h"
#include "singleton_assets.h"

#include "object_manager_generic.h"
#include "dynamic.h"

class entitiesManager : public objectManagerGeneric
{
private:
	std::vector<dynamic*> entities;
	gameMap* currentMap;

public:
	void update(float fElapsedTime) override;
	void draw() override;

private:
	void updateData() override;

	void updateEntities(float fElpasedTime);

	int drawCount;

	inline bool isVisible(int x, int y);

public:
	void addEntity(dynamic* entity);
	void removeEntity(dynamic* entity);
	void removeEntity(int id);
	dynamic* getEntity(int id);

	void setCurrentMap(gameMap* map);

	entitiesManager(Camera* camera);
	~entitiesManager();
};