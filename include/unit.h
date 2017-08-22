#ifndef COURSEWORK_UNITS_H
#define COURSEWORK_UNITS_H

#include <cursor.h>

class Unit {
protected:
	bool life;
	bool active;
	int angle;
	int health;
	HealthBar bar;
	RectangleShape rectangle;
	Texture texture;
	Sprite sprite;
public:
	Unit(Image & unit, Image &healthBar, const IntRect &rect, const Vector2f &pos, int health);
	virtual void update(float time,const Vector2f &mousePos) = 0;
	virtual void draw(RenderWindow &window) = 0;
	void setActive (bool active);
	bool getActive();
	virtual FloatRect getRect();
};


#endif