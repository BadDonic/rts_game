#include "unit.h"

Unit::Unit(Image &unitImage, Image &healthBar, const IntRect &rect, int health) : bar(healthBar) {
	texture.loadFromImage(unitImage);
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
	this->health = health;
	life = true;
	angle = 90;
	sprite.setOrigin(rect.width / 2, rect.height / 2);
}

FloatRect Unit::getRect() {
	return sprite.getGlobalBounds();
}
