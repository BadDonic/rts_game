#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class LifeBar {
public:
	Image image;
	Texture texture;
	Sprite sprite;
	int max;
	RectangleShape bar;
	LifeBar () {
		image.loadFromFile("../images/life.png");
		image.createMaskFromColor(Color(50, 96, 166));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(783, 2, 15, 84));
		bar.setFillColor(Color::Black);
		max = 100;
	}
	void update(int health) {
		if (health > 0 && health < max) {
			bar.setSize(Vector2f(10, (max - health) * 70 / max));
		}
	}

	void draw(RenderWindow &window) {
		Vector2f center = window.getView().getCenter();
		Vector2f size = window.getView().getSize();
		sprite.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 10);
		bar.setPosition(center.x - size.x / 2 + 14, center.y - size.y / 2 + 14);

		window.draw(sprite);
		window.draw(bar);
	}

};