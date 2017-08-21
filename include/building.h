#ifndef COURSEWORK_BUILDING_H
#define COURSEWORK_BUILDING_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "healthBar.h"
#include "icon.h"


using namespace sf;
using namespace std;

class Building {
	int health;
	bool life;
	bool active;
	int type;
	HealthBar healthBar;
	RectangleShape rectangle;
	Texture texture;
	Sprite sprite;
	void setType(int type);
	Building(Image &healthBar);
public:
	Building(Image &buildingImage, Image &healthBar, int type, Vector2f position);
	Building(int type, Image &healthBar,FloatRect &rect);
	void draw(RenderWindow &window);
	FloatRect getRect();
	void setActive(bool state);
	bool getActive();
	int getType();
};


#endif //COURSEWORK_BUILDING_H
