#include <healthBar.h>

HealthBar::HealthBar(Image &image) {
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(783, 2, height, width));
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
	Vector2f position(rect.left + (rect.width + width) / 2, rect.top - height);

	sprite.setPosition(position);
	bar.setPosition(position.x + 4, position.y + 4);
}

void HealthBar::draw(RenderWindow &window) {
	window.draw(sprite);
	window.draw(bar);
}

int HealthBar::getHeight() {
	return height;
}

int HealthBar::getWidth() {
	return width;
}
