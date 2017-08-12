#include "building.h"

Building::Building(Image &image, int type) {
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	health = 100;
	life = true;
}

void Building::draw(RenderWindow &window) {
	window.draw(sprite);
}
