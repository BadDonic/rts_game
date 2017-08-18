#include <healthBar.h>

HealthBar::HealthBar(Image &image) {
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(783, 2, 15, 84));
	sprite.setRotation(90);
	bar.setRotation(90);
	bar.setFillColor(Color::Black);
	max = 100;
}

void HealthBar::update(int health) {
	if (health > 0 && health < max)
		bar.setSize(Vector2f(10, (max - health) * 70 / max));
}

void HealthBar::setPosition(FloatRect rect) {
	Vector2f size(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	Vector2f position(rect.left + (rect.width + size.x) / 2, rect.top - size.y);

	sprite.setPosition(position);
	bar.setPosition(position.x + 4, position.y + 4);
}

void HealthBar::draw(RenderWindow &window) {
	window.draw(sprite);
	window.draw(bar);
}
