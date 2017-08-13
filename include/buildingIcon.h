#ifndef COURSEWORK_BULDINGICON_H
#define COURSEWORK_BULDINGICON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "resource.h"

using namespace sf;
using namespace std;

class BuildingIcon {
	int mineral;
	int gas;
	bool enable;
	string name;
	Image image;
	Texture texture;
	Sprite sprite;
public:
	BuildingIcon(String filePath, string name, IntRect rect, int mineral, int gas);
	void draw(RenderWindow &window, float posY);
	void drawPrice(RenderWindow &window, Font &font);
	void checkEnable(Resource &mineral, Resource &gas);
	int getMineralNumber();
	int getGasNumber();
	void subtractPrice(Resource &mineral, Resource &gas);
	bool isEnable();
	FloatRect getRect();
};


#endif //COURSEWORK_BULDINGICON_H
