
#include "building.h"

Building::Building(Image &image, String &name, float &x, float &y, int &width, int &height, int &health) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->health = health;
	life = true;
	isChosen = true;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin(width / 2, height / 2);
}
