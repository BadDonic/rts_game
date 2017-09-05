#include <cmath>
#include "unit.h"

Unit::Unit(Image &unitImage, Image &healthBar, const IntRect &rect, const Vector2f &pos, int healthMax) : bar(healthBar, healthMax) {
	texture.loadFromImage(unitImage);
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
	this->health = healthMax;
	life = true;
	select = false;
	isMove = false;
	angle = 0;
	currentFrame = 0;
	rectangle.setOutlineThickness(1);
	rectangle.setOutlineColor(Color::Green);
	rectangle.setFillColor(Color::Transparent);
	bar.update(health);
}

FloatRect Unit::getRect() {
	return rectangle.getGlobalBounds();
}

void Unit::setActive(bool active) {
	this->select = active;
}

bool Unit::isSelect() {
	return select;
}

void Unit::setDirection(const Vector2f &pos) {
	isMove = true;
	direction = pos;
}

