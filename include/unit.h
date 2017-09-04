#ifndef COURSEWORK_UNIT_H
#define COURSEWORK_UNIT_H

#include <SFML/Graphics.hpp>
#include <building.h>

using namespace std;
using namespace sf;

class Unit {
protected:
	bool life;
	bool select;
	bool isMove;
	int angle;
	int health;
	Vector2f direction;
	HealthBar bar;
	RectangleShape rectangle;
	Texture texture;
	Sprite sprite;
public:
	Unit(Image & unit, Image &healthBar, const IntRect &rect, const Vector2f &pos, int health);
	virtual void update(float time) = 0;
	virtual void draw(RenderWindow &window) = 0;
	void setActive(bool active);
	bool isSelect();
	virtual void setDirection(const Vector2f &pos) = 0;
	FloatRect getRect();
};


#endif //COURSEWORK_UNIT_H