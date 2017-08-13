//
// Created by daniel on 11.08.17.
//

#include "buildingIcon.h"

BuildingIcon::BuildingIcon(String filePath, string name, IntRect rect, int mineral, int gas) {
	this->mineral = mineral;
	this->gas = gas;
	this->name = name;
	image.loadFromFile("../image/" + filePath);
	image.createMaskFromColor(Color::Black);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
	sprite.setScale(2, 2);
}

void BuildingIcon::draw(RenderWindow &window, float posY) {
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();
	sprite.setPosition(center.x + size.x / 2 - 150, center.y - size.y / 2 + 222 + posY);
	window.draw(sprite);
}

void BuildingIcon::checkEnable(Resource &mineral, Resource &gas) {
	if (this->mineral > mineral.getNumber() || this->gas > gas.getNumber()) {
		sprite.setColor(Color::White);
		enable = false;
	}else {
		sprite.setColor(Color::Yellow);
		enable = true;
	}
}

void BuildingIcon::drawPrice(RenderWindow &window, Font &font) {
	Text text("", font, 14);
	text.setColor(Color::White);
	text.setString(name + "\nCost:\n" + to_string(mineral) + " minerals\n" + to_string(gas) + " gas");
	text.setPosition(sprite.getGlobalBounds().left - 20, sprite.getGlobalBounds().top + 72);
	window.draw(text);
}

FloatRect BuildingIcon::getRect() {
	return sprite.getGlobalBounds();
}

bool BuildingIcon::isEnable() {
	return enable;
}

int BuildingIcon::getMineralNumber() {
	return mineral;
}

int BuildingIcon::getGasNumber() {
	return gas;
}

void BuildingIcon::subtractPrice(Resource &mineral, Resource &gas) {
	mineral.setNumber(mineral.getNumber() - this->mineral);
	gas.setNumber(gas.getNumber() - this->gas);
	checkEnable(mineral,gas);
}
