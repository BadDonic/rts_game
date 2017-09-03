#include <iostream>
#include <building.h>
#include "cursor.h"
#include <list>

Cursor::Cursor(Image * buildingImage) {
	click = false;
	defaultImage.loadFromFile("../image/cursor.png");
	buildingsImage = buildingImage;
	type = Default;
	this->setCursorType(type);
	rectangle.setOutlineThickness(1);
	rectangle.setOutlineColor(Color::Green);
	rectangle.setFillColor(Color::Transparent);
}

void Cursor::setCursorPosition(Vector2f position) {
	sprite.setPosition(position.x , position.y);
}

void Cursor::drawRectangle(RenderWindow &window) {
	window.draw(rectangle);
}

void Cursor::setRectangleSize(Vector2f size) {
	if (size.x == 0 && size.y == 0) rectangle.setSize(size);
	else rectangle.setSize(size - rectangle.getPosition());
}

void Cursor::setRectanglePosition(Vector2f position) {
	rectangle.setPosition(position);
}

void Cursor::drawCursor(RenderWindow &window, list<Unit *>& unitList, list<Building *>& buildingList) {
	if (click) {
		drawRectangle(window);
	}else if (type != Default) {
		correctPlace = checkCorrectPlace(window, unitList, buildingList);
		rectangle.setPosition(sprite.getPosition() - Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2));
		drawRectangle(window);
	}
	window.draw(sprite);

}

bool Cursor::isClicked() {
	return click;
}

void Cursor::setClick(bool click) {
	this->click = click;
}

void Cursor::setCursorType(int type) {
	this->type = type;
	switch (this->type) {
		case Default: {
			texture.loadFromImage(defaultImage);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(8, 7, 32, 32));
			sprite.setOrigin(0, 0);
			rectangle.setSize(Vector2f(0, 0));
			rectangle.setOutlineColor(Color::Green);
			sprite.setColor(Color::Green);
			break;
		}
		case CommandCenter: {
			texture.loadFromImage(*buildingsImage);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, 128, 100));
			sprite.setOrigin(64, 50);
			sprite.setScale(1.2, 1.2);
			sprite.setColor(Color::Green);
			rectangle.setSize(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
			break;
		}
		default:break;
	}
}

int Cursor::getType() {
	return type;
}

bool Cursor::checkCorrectPlace(RenderWindow &window, list<Unit *>& unitList, list<Building *>& buildingList) {
	Vector2f rectPos = rectangle.getPosition();
	Vector2f rectSize = rectangle.getSize();

	if (rectPos.x < 0 || rectPos.y < 0 || rectPos.y + rectSize.y > 3072 || rectPos.x + rectSize.x > 3072) {
		rectangle.setOutlineColor(Color::Red);
		sprite.setColor(Color::Red);
		return false;
	}

	for (auto &it : buildingList)
		if (rectangle.getGlobalBounds().intersects(it->getRect())) {
			rectangle.setOutlineColor(Color::Red);
			sprite.setColor(Color::Red);
			return false;
		}
	for (auto &it : unitList)
		if (rectangle.getGlobalBounds().intersects(it->getRect())) {
			rectangle.setOutlineColor(Color::Red);
			sprite.setColor(Color::Red);
			return false;
		}

	rectangle.setOutlineColor(Color::Green);
	sprite.setColor(Color::Green);
	return true;
}

bool Cursor::getCorrectPlace() {
	return correctPlace;
}

Vector2f Cursor::getPosition() {
	return sprite.getPosition();
}

FloatRect Cursor::getRect() {
	return rectangle.getGlobalBounds();
}