//
// Created by daniel on 08.08.17.
//

#include <iostream>
#include <building.h>
#include "cursor.h"

Cursor::Cursor() {
	click = false;
	defaultImage.loadFromFile("../image/cursor.png");
	buildingsImage.loadFromFile("../image/TerranBuilding.png");
	type = Default;
	this->setCursorType(type);
	rectangle.setOutlineThickness(1);
	rectangle.setOutlineColor(Color::Green);
	rectangle.setFillColor(Color::Transparent);
}

void Cursor::setCursorPosition(Vector2f position) {
	sprite.setPosition(position.x - 57, position.y - 44);
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

void Cursor::drawCursor(RenderWindow &window) {
	window.draw(sprite);
	if (click) {
		drawRectangle(window);
	}else if (type != Default) {
		rectangle.setPosition(sprite.getPosition() - Vector2f(rectangle.getSize().x / 2, rectangle.getSize().y / 2));
		drawRectangle(window);
	}
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
			sprite.setTextureRect(IntRect(0, 0, 32, 32));
			sprite.setOrigin(16, 16);
			break;
		}
		case CommandCenter: {
			texture.loadFromImage(buildingsImage);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, 128, 100));
			sprite.setOrigin(64, 50);
			sprite.setScale(1.2, 1.2);
			sprite.setColor(Color::Green);
			rectangle.setSize(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
			break;
		}
	}
}

int Cursor::getType() {
	return type;
}
