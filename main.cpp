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

	Clock clock;
	float currentFrame = 0;


	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 500;


		Event event;
		while (window.pollEvent(event)) if (event.type == Event::Closed) window.close();

		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			currentFrame += 0.005 * time;
			if (currentFrame > 3) currentFrame = 0;
			heroSprite.setTextureRect(IntRect(96 * (int)currentFrame, 96, 96, 96));
			heroSprite.move((float)-0.1 * time, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			currentFrame += 0.005 * time;
			if (currentFrame > 3) currentFrame = 0;
			heroSprite.setTextureRect(IntRect(96 * (int)currentFrame, 192, 96, 96));
			heroSprite.move((float)0.1 * time, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			currentFrame += 0.005 * time;
			if (currentFrame > 3) currentFrame = 0;
			heroSprite.setTextureRect(IntRect(96 * (int)currentFrame, 288, 96, 96));
			heroSprite.move(0, (float)-0.1 * time);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			currentFrame += 0.005 * time;
			if (currentFrame > 3) currentFrame = 0;
			heroSprite.setTextureRect(IntRect(96 * (int)currentFrame, 0, 96, 96));
			heroSprite.move(0, (float)0.1 * time);
		}

		window.clear();
		window.draw(heroSprite);
		window.display();
	}

	return EXIT_SUCCESS;
}