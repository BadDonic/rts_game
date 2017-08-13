#include <cursor.h>
#include "building.h"


Building::Building(Image &image, int type, Vector2f position) {
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	setType(type);
	sprite.setPosition(position);
}

void Building::draw(RenderWindow &window) {
	window.draw(sprite);
}

void Building::setType(int type) {
	this->type = type;
	switch (type) {
		case CommandCenter: {
			sprite.setTextureRect(IntRect(0, 0, 128, 100));
			sprite.setOrigin(64, 50);
			break;
		}
	}
}
