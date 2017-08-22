#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class HealthBar {
	int width = 84;
	int height = 15;
	Texture texture;
	Sprite sprite;
	int max;
	RectangleShape bar;
public:
	HealthBar(Image &image, int max);
	void update(int health);
	void setPosition(FloatRect rect);
	void draw(RenderWindow &window);
	void setScale(float factX, float factY);
	int getHeight();
	int getWidth();

};