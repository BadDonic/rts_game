//
// Created by daniel on 08.08.17.
//

#include "cursor.h"

Cursor::Cursor() {
	defaultImage.loadFromFile("../image/cursor.png");
	texture.loadFromImage(defaultImage);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 32, 32));
	sprite.setOrigin(16, 16);
}

void Cursor::setCursorPosition(Vector2f position) {
	sprite.setPosition(position.x - 57, position.y - 44);
}

void Cursor::draw(RenderWindow &window) {
	window.draw(sprite);
}
