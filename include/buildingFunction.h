#ifndef COURSEWORK_BUILDINGFUNCTION_H
#define COURSEWORK_BUILDINGFUNCTION_H


#include <list>
#include "icon.h"

class BuildingFunction {
public:
	bool drawCivilian;
	bool drawMarine;
	bool enableSelectPos;
	list<Icon *> functions;
	Icon civilian = Icon("icons.png", "Civilian", IntRect(180, 0, 33, 34), 50, 20);
	Icon marine = Icon("icons.png", "Marine", IntRect(0, 32, 33, 34), 50, 20);
	Icon selectPos =Icon("icons.png", "SelectPosition", IntRect(396, 340, 33, 34), 0, 0);
	BuildingFunction(Resource &mineral, Resource &gas);
	void setType(int type);
	void draw(RenderWindow &window, Font &font);
};


#endif
