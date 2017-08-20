#ifndef COURSEWORK_BUILDINGFUNCTION_H
#define COURSEWORK_BUILDINGFUNCTION_H


#include <list>
#include "icon.h"

class BuildingFunction {
public:
	list<Icon> functions;
	Icon civilian = Icon("icons.png", "Civilian", IntRect(180, 0, 33, 34), 50, 20);
	Icon marine = Icon("icons.png", "Marine", IntRect(0, 32, 33, 34), 50, 20);
	Icon selectPos =Icon("icons.png", "SelectPosition", IntRect(384, 340, 33, 36), 0, 0);
	void setType(int type);
	void draw(RenderWindow &window);
};


#endif
