#include <cursor.h>
#include "buildingFunction.h"


void BuildingFunction::setType(int type) {
	functions.clear();
	if (type != SupplyDepot ) {
		functions.push_back(selectPos);
		if (type == CommandCenter)  {
			functions.push_back(civilian);
			cout << "Hi" << endl;
		}else functions.push_back(marine);
	}
}

void BuildingFunction::draw(RenderWindow &window) {
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize() / (float) 2;
	int space = 0;
	for (auto it : functions) {
		it.draw(window, center + Vector2f(-size.x, size.y) + Vector2f(0.45 * 2 * size.x + space,- 100));
		space += 150;
	}
}

