#include "resource.h"

Resource::Resource(String filePath, int max, int x, int y, int width, int height) {
	number = 0;
	this->max = max;
	image.loadFromFile("../image/" + filePath);
	texture.loadFromImage(this->image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(x, y, width, height));
}

void Resource::draw(RenderWindow &window, Font &font, int posX, int posY) {
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();
	sprite.setPosition(center.x - size.x / 2 + 10 + posX, center.y - size.y / 2 + 10 + posY);
	Text text("", font, 12);
	text.setColor(Color::White);
	text.setStyle(sf::Text::Bold);
	text.setString(": " + to_string(number) + " / " + to_string(max));
	text.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width + 10, sprite.getPosition().y + sprite.getGlobalBounds().height / 2);
	window.draw(sprite);
	window.draw(text);
}

void Resource::setScale(float factorX, float factorY) {
	sprite.setScale(factorX, factorY);
}
