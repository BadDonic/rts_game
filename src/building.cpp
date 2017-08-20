#include <cursor.h>
#include <icon.h>

Building::Building() {
	active = false;
	life = true;
	health = 100;
	rectangle.setOutlineThickness(1);
	rectangle.setOutlineColor(Color::Green);
	rectangle.setFillColor(Color::Transparent);
}

Building::Building(Image &image, HealthBar * bar, int type, Vector2f position) : Building() {
	healthBar = bar;
	healthBar->update(health);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	setType(type);
	sprite.setPosition(position);
	healthBar->setPosition(getRect());
	rectangle.setPosition(position.x - sprite.getOrigin().x, position.y - sprite.getOrigin().y - healthBar->getHeight());
	rectangle.setSize(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height + healthBar->getHeight()));
}

Building::Building(int type, FloatRect &rect) : Building() {
	healthBar = nullptr;
	this->type = type;
	rectangle.setSize(Vector2f(rect.width, rect.height));
	rectangle.setPosition(rect.left, rect.top);
}

void Building::draw(RenderWindow &window) {
	if (active) window.draw(rectangle);
	if (type != Gas && type != Mineral)  {
		window.draw(sprite);
		healthBar->draw(window);
	}
}

void Building::setType(int type) {
	this->type = type;
	switch (type) {
		case CommandCenter: {
			sprite.setTextureRect(IntRect(0, 0, 128, 100));
			sprite.setOrigin(64, 50);
			break;
		}
		default:break;
	}
}
FloatRect Building::getRect() {
	if (type == Mineral || type == Gas) return rectangle.getGlobalBounds();
	return sprite.getGlobalBounds();
}

void Building::setActive(bool state) {
	active = state;
}

bool Building::getActive() {
	return active;
}

