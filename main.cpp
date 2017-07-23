#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
	RenderWindow window(VideoMode(640, 480), "SMFL works!");

	Texture texture;
	texture.loadFromFile("../images/hero.png");

	Sprite heroSprite;
	heroSprite.setTexture(texture);
	heroSprite.setPosition(50, 25);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) if (event.type == Event::Closed) window.close();

		window.clear();
		window.draw(heroSprite);
		window.display();
	}

	return EXIT_SUCCESS;
}