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
	float buildTime;
	bool enable;
	Image image;
	Texture texture;
	Sprite sprite;
public:
	BuildingIcon(String filePath, IntRect rect, int mineral, int gas, float buildTime);
	void draw(RenderWindow &window, float posY);
	void drawPrice(RenderWindow &window, Font &font);
	void checkEnable(int numberOfMineral, int numberOfGas);
	bool isEnable();
	FloatRect getRect();
};


#endif //COURSEWORK_BULDINGICON_H
