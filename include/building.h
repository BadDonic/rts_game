#ifndef COURSEWORK_BUILDING_H
#define COURSEWORK_BUILDING_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Building {
public:
	float x, y;
	int width, height, health;
	bool life, isChosen;
	Texture texture;
	Sprite sprite;
	String name;
	Building(Image &image, String &name, float &x, float &y, int &width, int &height, int &health);
	virtual void update(float time) = 0;
};


#endif //COURSEWORK_BUILDING_H
