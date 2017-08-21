#include <cursor.h>

Building::Building(Image &healthBarImage) : healthBar(healthBarImage){
	active = false;
	life = true;
	health = 100;
	rectangle.setOutlineThickness(1);
	rectangle.setOutlineColor(Color::Green);
	rectangle.setFillColor(Color::Transparent);
	healthBar.update(health);
}

Building::Building(Image &image, Image &healthBarImage, int type, Vector2f position) : Building(healthBarImage) {
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	setType(type);
	sprite.setPosition(position);
	healthBar.setPosition(getRect());
	rectangle.setPosition(position.x - sprite.getOrigin().x, position.y - sprite.getOrigin().y - healthBar.getHeight());
	rectangle.setSize(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height + healthBar.getHeight()));
}

Building::Building(int type, Image &healthBar, FloatRect &rect) : Building(healthBar) {
	this->type = type;
	rectangle.setSize(Vector2f(rect.width, rect.height));
	rectangle.setPosition(rect.left, rect.top);
}

void Building::draw(RenderWindow &window) {
	if (active) window.draw(rectangle);
	if (type != Gas && type != Mineral)  {
		window.draw(sprite);
		healthBar.draw(window);
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

int Building::getType() {
	return type;
}