#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class HealthBar {
	Texture texture;
	Sprite sprite;
	int max;
	RectangleShape bar;
public:
	HealthBar(Image &image);
	void update(int health);
	void setPosition(FloatRect rect);
	void draw(RenderWindow &window);

};