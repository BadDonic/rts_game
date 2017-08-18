#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class HealthBar {
public:
	Texture texture;
	Sprite sprite;
	int max;
	RectangleShape bar;

	HealthBar(Image &image);
	void update(int health);
	void draw(RenderWindow &window, FloatRect rect);

};