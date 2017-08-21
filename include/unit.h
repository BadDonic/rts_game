#ifndef COURSEWORK_UNITS_H
#define COURSEWORK_UNITS_H

#include <cursor.h>

class Unit {
private:
	bool life;
	int angle;
	int health;
	HealthBar bar;
	RectangleShape rect;
	Texture texture;
	Sprite sprite;
public:
	Unit(Image & unit, Image &healthBar, const IntRect &rect, int health);

	virtual void update(float time) = 0;
	virtual void draw(RenderWindow &window) = 0;

	virtual FloatRect getRect();
};


#endif