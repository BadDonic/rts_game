#ifndef COURSEWORK_BUILDING_H
#define COURSEWORK_BUILDING_H

#include <SFML/Graphics.hpp>
#include <iostream>


using namespace sf;
using namespace std;

class Building {
	int health;
	bool life;
	int type;
	int mode;
	Texture texture;
	Sprite sprite;
	void setType(int type);
public:
	Building(Image &image, int type, Vector2f position);
	void draw(RenderWindow &window);
};


#endif //COURSEWORK_BUILDING_H
