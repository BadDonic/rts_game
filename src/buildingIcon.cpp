//
// Created by daniel on 11.08.17.
//

#include "buildingIcon.h"

BuildingIcon::BuildingIcon(String filePath, IntRect rect, int mineral, int gas, float buildTime) {
	this->mineral = mineral;
	this->gas = gas;
	this->buildTime = buildTime;
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

void BuildingIcon::checkEnable(int numberOfMineral, int numberOfGas) {
	if (mineral > numberOfMineral || gas > numberOfGas) {
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
	text.setString( "Cost:\n" + to_string(mineral) + " minerals\n" + to_string(gas) + " gas\nTime : " + to_string((int)buildTime) + " sec");
	text.setPosition(sprite.getGlobalBounds().left - 15, sprite.getGlobalBounds().top + 72);
	window.draw(text);
}

FloatRect BuildingIcon::getRect() {
	return sprite.getGlobalBounds();
}

bool BuildingIcon::isEnable() {
	return enable;
}
