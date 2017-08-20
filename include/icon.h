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
	bool enable;
	string name;
	Image image;
	Texture texture;
	Sprite sprite;
public:
	Icon(String filePath, string name, IntRect rect, int mineral, int gas);
	void setPosition(RenderWindow &window);
	void draw(RenderWindow &window, Vector2f position);
	void drawPrice(RenderWindow &window, Font &font);
	void checkEnable(Resource &mineral, Resource &gas);
	int getMineralNumber();
	int getGasNumber();
	void subtractPrice(Resource &mineral, Resource &gas);
	bool isEnable();
	FloatRect getRect();
};


#endif
