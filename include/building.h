#ifndef COURSEWORK_BUILDING_H
#define COURSEWORK_BUILDING_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "healthBar.h"


using namespace sf;
using namespace std;

class Building {
	int health;
	bool life;
	HealthBar * healthBar;
	bool active;
	int type;
	int mode;
	RectangleShape rectangle;
	Texture texture;
	Sprite sprite;
	void setType(int type);
	Building();
public:
	Building(Image &buildingImage, HealthBar * healthBar, int type, Vector2f position);
	Building(int type, FloatRect &rect);
	void draw(RenderWindow &window);
	FloatRect getRect();
	void setActive(bool state);
	bool getActive();
};


#endif //COURSEWORK_BUILDING_H
