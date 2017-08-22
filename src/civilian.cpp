#include "civilian.h"

Civilian::Civilian(Image &unitImage, Image &healthBarImage, const IntRect &rect, const Vector2f &pos, int health) : Unit(unitImage, healthBarImage, rect, pos, health) {
	sprite.setScale(1.7, 1.7);
	sprite.setOrigin(rect.width / 2, rect.height / 2);
	sprite.setPosition(pos);
	bar.setScale(1, 1);
	bar.setPosition(sprite.getGlobalBounds());
	rectangle.setSize(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
	rectangle.setPosition(sprite.getPosition().x - sprite.getGlobalBounds().width / 2,sprite.getPosition().y - sprite.getGlobalBounds().height / 2 + 2);
}

void Civilian::update(float time, const Vector2f &mousePos) {

}

void Civilian::draw(RenderWindow &window) {
	window.draw(sprite);
	bar.draw(window);
	if (active) window.draw(rectangle);
}
