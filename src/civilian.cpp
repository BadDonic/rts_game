//
// Created by daniel on 21.08.17.
//

#include "civilian.h"

Civilian::Civilian(Image &unitImage, Image &healthBarImage, const IntRect &rect, const Vector2f &pos, int health) : Unit(unitImage, healthBarImage, rect, pos, health) {
	sprite.setScale(1.5, 1.5);
	sprite.setPosition(pos);
	rectangle.setSize(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height + bar.getHeight()));
	rectangle.setPosition(pos.x - sprite.getOrigin().x, pos.y - sprite.getOrigin().y - bar.getHeight());
}

void Civilian::update(float time, const Vector2f &mousePos) {

}

void Civilian::draw(RenderWindow &window) {
	window.draw(sprite);
	bar.draw(window);
	if (active) window.draw(rectangle);
}
