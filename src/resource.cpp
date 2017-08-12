#include "resource.h"

Resource::Resource(const String &filePath,const int &startNumber, const int &max, const IntRect &rect, const Vector2f &scale) {
	number = startNumber;
	this->max = max;
	image.loadFromFile("../image/" + filePath);
	texture.loadFromImage(this->image);
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
	sprite.setScale(scale);
}

void Resource::draw(RenderWindow &window, Font &font, int posX) {
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();
	sprite.setPosition(center.x - size.x / 2 + 10 + posX, center.y - size.y / 2 + 10);
	Text text("", font, 16);
	text.setColor(Color::White);
	text.setStyle(sf::Text::Bold);
	text.setString(": " + to_string(number) + " / " + to_string(max));
	text.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width + 10, sprite.getPosition().y + sprite.getGlobalBounds().height / 2 - 10);
	window.draw(sprite);
	window.draw(text);
}


int Resource::getNumber() {
	return number;
}
