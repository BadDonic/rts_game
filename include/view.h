#include <SFML/Graphics.hpp>

using namespace sf;

View view;

void setPlayerCoordinatesForView(float x, float y) {
	float tempX = x; float tempY = y;

	if (x < 512) tempX = 512;
	if (x > 768) tempX = 768;
	if (y < 384) tempY = 384;
	if (y > 416) tempY = 416;

	view.setCenter(tempX, tempY);
}