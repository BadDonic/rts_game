#ifndef COURSEWORK_UNITS_H
#define COURSEWORK_UNITS_H

#include <cursor.h>

class Unit {
	bool life;
	int health;
	int maxHealth;
	HealthBar & bar;
	RectangleShape rect;
	Texture &texture;
	Sprite &sprite;
};


#endif
