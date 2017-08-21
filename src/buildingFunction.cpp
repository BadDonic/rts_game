#include <cursor.h>
#include "buildingFunction.h"

BuildingFunction::BuildingFunction(Resource &mineral, Resource &gas) {
	civilian.checkEnable(mineral, gas);
	selectPos.checkEnable(mineral, gas);
	marine.checkEnable(mineral, gas);
}

void BuildingFunction::setType(int type) {
	functions.clear();
	if (type != SupplyDepot  && type != Mineral && type != Gas) {
		//>>>functions.push_back(&selectPos);
		if (type == CommandCenter) functions.push_back(&civilian);
		else functions.push_back(&marine);
	}
}

void BuildingFunction::draw(RenderWindow &window, Font &font) {
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize() / (float) 2;
	int spaceX = 0;
	int spaceY = 0;
	for (auto it : functions) {
		it->draw(window, center + Vector2f(-size.x, size.y) + Vector2f(0.45 * 2 * size.x + spaceX,- 70 + spaceY));
		spaceX += 100;
		spaceY -= 10;
	}
	Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	if (civilian.getRect().contains(mousePos))
		civilian.drawPrice(window, font);
	else if (selectPos.getRect().contains(mousePos))
		selectPos.drawPrice(window, font);
	else if (marine.getRect().contains(mousePos))
		marine.drawPrice(window, font);
}

