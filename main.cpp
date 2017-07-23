#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
	RenderWindow window(VideoMode(640, 480), "SMFL works!");

	Texture texture;
	texture.loadFromFile("../images/hero.png");

	Sprite heroSprite;
	heroSprite.setTexture(texture);
	heroSprite.setTextureRect(IntRect(0, 192, 96, 96));
	heroSprite.setPosition(250, 250);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) if (event.type == Event::Closed) window.close();

		if (Keyboard::isKeyPressed(Keyboard::Left)) { heroSprite.move((float)-0.1, 0); heroSprite.setTextureRect(IntRect(0, 96, 96, 96));}
		if (Keyboard::isKeyPressed(Keyboard::Right)) { heroSprite.move(0.1, 0); heroSprite.setTextureRect(IntRect(0, 192, 96, 96)); }
		if (Keyboard::isKeyPressed(Keyboard::Up)) { heroSprite.move(0, (float)-0.1); heroSprite.setTextureRect(IntRect(0, 288, 96, 96)); }
		if (Keyboard::isKeyPressed(Keyboard::Down)) { heroSprite.move(0, 0.1); heroSprite.setTextureRect(IntRect(0, 0, 96, 96)); }

		if (Mouse::isButtonPressed(Mouse::Left)) heroSprite.setColor(Color::Blue);
		if (Mouse::isButtonPressed(Mouse::Right)) heroSprite.setColor(Color::Red);

		window.clear();
		window.draw(heroSprite);
		window.display();
	}

	return EXIT_SUCCESS;
}