#include "player.h"

void Player::drawResources(RenderWindow &window, Font &font) {
	mineral.draw(window, font, 15, 0);
	gas.draw(window, font, 200, 0);
	unit.draw(window, font, 400, 0);
}

Player::Player() {
	mineral.setScale(0.3, 0.3);
	gas.setScale(0.2, 0.2);
	unit.setScale(0.6, 0.6);
}
