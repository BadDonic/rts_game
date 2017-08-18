#ifndef COURSEWORK_PLAYER_H
#define COURSEWORK_PLAYER_H


#include <list>
#include "resource.h"
#include "cursor.h"
#include "buildingIcon.h"
#include "building.h"

class Player {
	Image * buildingImage;
	void setPlayerCoordinatesForView(double &x, double &y);
public:
	View view;
	Cursor cursor;
	Resource mineral = Resource("mineral.png", 200, 1000, IntRect(0, 0, 144, 144), Vector2f(0.3, 0.3));
	Resource gas = Resource("gas.png", 100, 150, IntRect(0, 0, 256, 256), Vector2f(0.2, 0.2));
	Resource unit = Resource("unit.jpg", 0, 7, IntRect(228, 532, 76, 76), Vector2f(0.6, 0.6));
	BuildingIcon commandCenter = BuildingIcon("CmdIconsDisabled.png", "CommandCenter", IntRect(288, 136, 33, 34), 100, 0);


	Player(Vector2u size, Image &buildingImage);
	void drawResources(RenderWindow &window, Font &font);
	void drawBuildingIcons(RenderWindow &window, Font &font);
	void control(RenderWindow &window, list<Building *> * buildingList, double &time);
};


#endif
