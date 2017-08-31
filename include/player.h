#ifndef COURSEWORK_PLAYER_H
#define COURSEWORK_PLAYER_H


#include <list>
#include "resource.h"
#include "cursor.h"
#include "icon.h"
#include "building.h"
#include "buildingFunction.h"
#include "unit.h"

class Player {
	Image * buildingImage;
	Image * healthBarImage;
	Image * civilianImage;
	void setPlayerCoordinatesForView(double &x, double &y);
public:
	View view;
	Cursor cursor;
	Resource mineral = Resource("mineral.png", 1500, 2000, IntRect(0, 0, 144, 144), Vector2f(0.3, 0.3));
	Resource gas = Resource("gas.png", 100, 150, IntRect(0, 0, 256, 256), Vector2f(0.2, 0.2));
	Resource unit = Resource("unit.jpg", 0, 7, IntRect(228, 532, 76, 76), Vector2f(0.6, 0.6));
	Icon commandCenter = Icon("icons.png", "CommandCenter", IntRect(288, 136, 33, 34), 500, 0);

	Player(Vector2u size, Image *buildingImage, Image *healthBarImage, Image * civilianImage);
	void drawResources(RenderWindow &window, Font &font);
	void drawBuildingIcons(RenderWindow &window, Font &font);
	void control(RenderWindow &window, list<Building *> * buildings, list<Unit *> * units, BuildingFunction &functionsList, float &time);
};


#endif
