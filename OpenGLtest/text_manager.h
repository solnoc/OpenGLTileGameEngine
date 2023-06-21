#pragma once

#include "game_maps.h"
#include "singleton_assets.h"

#include "object_manager_generic.h"
#include "dynamic.h"

class textManager : public objectManagerGeneric
{
private:
	dynamic* current_text;

public:
	void draw() override;

private:
	void updateData() override;

	inline bool isVisible(int x, int y);

public:
	void changeText(dynamic* entity);

	void setCurrentMap(gameMap* map);

	bool displayText;

	textManager(Camera* camera);
	~textManager();
};