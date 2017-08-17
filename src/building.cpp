#include <cursor.h>
#include "building.h"


Building::Building(Image &image, int type, Vector2f position) {
	active = false;
	life = true;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	setType(type);
	sprite.setPosition(position);
	rectangle.setOutlineThickness(1);
	rectangle.setOutlineColor(Color::Green);
	rectangle.setFillColor(Color::Transparent);
	rectangle.setPosition(position - sprite.getOrigin());
	rectangle.setSize(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
}

void Building::draw(RenderWindow &window) {
	if (active) window.draw(rectangle);
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
FloatRect Building::getRect() {
	return sprite.getGlobalBounds();
}

void Building::setActive(bool state) {
	active = state;
}

bool Building::getActive() {
	return active;
}
