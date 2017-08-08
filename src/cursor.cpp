//
// Created by daniel on 08.08.17.
//

#include "cursor.h"

Cursor::Cursor() {
	defaultImage.loadFromFile("../image/cursor.png");
	texture.loadFromImage(defaultImage);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 32, 32));
}

void Cursor::setCursorPosition(double x, double y) {
	sprite.setPosition(x, y);
}
