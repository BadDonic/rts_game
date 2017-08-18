#include "player.h"


Player::Player(Vector2u size, Image &buildingImage) : cursor(&buildingImage) {
	view.setSize(size.x, size.y);
	view.setCenter(size.x / 2, size.y / 2);
	commandCenter.checkEnable(mineral, gas);
	this->buildingImage = &buildingImage;
}

void Player::drawResources(RenderWindow &window, Font &font) {
	mineral.draw(window, font, 15);
	gas.draw(window, font, 200);
	unit.draw(window, font, 400);
}


void Player::setPlayerCoordinatesForView(double &x, double &y) {
	double tempX = x;
	double tempY = y;
	double minX = this->view.getSize().x / 2;
	double minY = view.getSize().y / 2;
	double max = 96 * 32;

	if (x < minX) tempX = minX;
	if (x > max - minX) tempX = max - minX;
	if (y < minY) tempY = minY;
	if (y > max - minY) tempY = max - minY;

	view.setCenter(tempX, tempY);
}

void Player::control(RenderWindow &window, list<Building *> * buildingList, double &time) {
	Event event = {};
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) window.close();

		if (event.type == Event::MouseButtonPressed) {
			if (event.key.code == Mouse::Left) {
				for (auto &it : *buildingList) {
					if (it->getActive()) it->setActive(false);
				}

				if (cursor.getType() == Default) {
					if (commandCenter.getRect().contains(window.mapPixelToCoords(Mouse::getPosition(window)))  && commandCenter.isEnable()) {
						cursor.setCursorType(CommandCenter);
					}else {
						cursor.setRectanglePosition(window.mapPixelToCoords(Mouse::getPosition(window)));
						cursor.setClick(true);
					}

					for (auto &it : *buildingList) {
						if (it->getRect().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
							it->setActive(true);
					}

				}else {
					buildingList->push_back(new Building(*buildingImage, cursor.getType(), window.mapPixelToCoords(Mouse::getPosition(window))));
					commandCenter.subtractPrice(mineral, gas);
					cursor.setCursorType(Default);
				}
			}

			if (event.key.code == Mouse::Right) {
				if (cursor.getType() != Default) cursor.setCursorType(Default);
			}
		}

		if (event.type == Event::MouseMoved) {
			if (cursor.getType() == Default) {
				if (cursor.isClicked())
					cursor.setRectangleSize(window.mapPixelToCoords(Mouse::getPosition(window)));
			}
		}

		if (event.type == Event::MouseButtonReleased) {
			if (cursor.getType() == Default) {
				if (cursor.isClicked()) {
					cursor.setClick(false);
					cursor.setRectangleSize(Vector2f(0, 0));
				}
			}
		}

	}

	double tempX = view.getCenter().x;
	double tempY = view.getCenter().y;
	double viewCenterX = tempX;
	double viewCenterY = tempY;
	Vector2i localPosition= Mouse::getPosition(window);

	if (Keyboard::isKeyPressed(Keyboard::D) || localPosition.x > window.getSize().x-3) {
		tempX += 0.5*time;
	}
	if (Keyboard::isKeyPressed(Keyboard::S) || localPosition.y > window.getSize().y-3) {
		tempY += 0.5*time;
	}
	if (Keyboard::isKeyPressed(Keyboard::A) || localPosition.x < 3) {
		tempX += -0.5*time;
	}
	if (Keyboard::isKeyPressed(Keyboard::W) || localPosition.y < 3) {
		tempY += -0.5*time;
	}
	setPlayerCoordinatesForView(tempX, tempY);
	if ((viewCenterX != view.getCenter().x || viewCenterY != view.getCenter().y) && cursor.isClicked())
		cursor.setRectangleSize(window.mapPixelToCoords(Mouse::getPosition(window)) + Vector2f(view.getCenter().x - viewCenterX, view.getCenter().y - viewCenterY));
}

void Player::drawBuildingIcons(RenderWindow &window, Font &font) {
	commandCenter.draw(window, 0);
	if (commandCenter.getRect().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
		commandCenter.drawPrice(window, font);
}
