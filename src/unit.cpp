#include "unit.h"

Unit::Unit(Image &unitImage, Image &healthBar, const IntRect &rect, const Vector2f &pos, int health) : bar(healthBar) {
	texture.loadFromImage(unitImage);
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
	this->health = health;
	life = true;
	active = false;
	angle = 90;
	sprite.setOrigin(rect.width / 2, rect.height / 2);
	rectangle.setOutlineThickness(1);
	rectangle.setOutlineColor(Color::Green);
	rectangle.setFillColor(Color::Transparent);
	bar.setPosition(sprite.getGlobalBounds());
	bar.update(health);
}

FloatRect Unit::getRect() {
	return rectangle.getGlobalBounds();
}

void Unit::setActive(bool active) {
	this->active = active;
}

bool Unit::getActive() {
	return active;
}

