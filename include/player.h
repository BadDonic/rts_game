#ifndef COURSEWORK_PLAYER_H
#define COURSEWORK_PLAYER_H


#include "resource.h"
#include "cursor.h"

class Player {
public:
	Cursor cursor;
	Resource mineral = Resource("mineral.png", 1000, 0, 0, 144, 144);
	Resource gas = Resource("gas.png", 150, 0, 0, 256, 256);
	Resource unit = Resource("unit.jpg", 7, 228, 532, 76, 76);
	Player();
	void drawResources(RenderWindow &window, Font &font);
};


#endif
