#ifndef RESOURCE_H
#define RESOURCE_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Resource {
	int number;
	int max;
	Image image;
	Texture texture;
	Sprite sprite;
public:
	Resource(const String &filePath, int startNumber, int max,const IntRect &rect, Vector2f scale);
	void draw(RenderWindow &window, Font &font, int posX);
	int getNumber();
};

#endif RES
