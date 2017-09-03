#ifndef COURSEWORK_ICON_H
#define COURSEWORK_ICON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "resource.h"

using namespace sf;
using namespace std;

class Icon {
	int mineral;
	int gas;
	int unit;
	bool enable;
	string name;
	Image image;
	Texture texture;
	Sprite sprite;
public:
	Icon(String filePath, string name, IntRect rect, int mineral, int gas, int unit);
	void draw(RenderWindow &window, const Vector2f &position, Resource &mineral, Resource &gas, Resource &unit);
	void drawPrice(RenderWindow &window, Font &font);
	void checkEnable(Resource &mineral, Resource &gas, Resource &unit);
	int getMineralNumber();
	int getGasNumber();
	void subtractPrice(Resource &mineral, Resource &gas, Resource &unit);
	bool isEnable();
	FloatRect getRect();
};


#endif
