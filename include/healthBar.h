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
	HealthBar(Image &image);
	void update(int health);
	void setPosition(FloatRect rect);
	void draw(RenderWindow &window);
	int getHeight();
	int getWidth();

};