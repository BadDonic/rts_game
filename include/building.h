#ifndef COURSEWORK_BUILDING_H
#define COURSEWORK_BUILDING_H

#include <SFML/Graphics.hpp>
#include <iostream>


using namespace sf;
using namespace std;

class Building {
	int health;
	bool life;
	bool active;
	int type;
	int mode;
	RectangleShape rectangle;
	Texture texture;
	Sprite sprite;
	void setType(int type);
public:
	Building(Image &image, int type, Vector2f position);
	void draw(RenderWindow &window);
	FloatRect getRect();
	void setActive(bool state);
	bool getActive();
};


#endif //COURSEWORK_BUILDING_H
