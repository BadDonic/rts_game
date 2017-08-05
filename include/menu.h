#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

void menu(RenderWindow &window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, backgroundTexture;
	menuTexture1.loadFromFile("../images/111.png");
	menuTexture2.loadFromFile("../images/222.png");
	menuTexture3.loadFromFile("../images/333.png");
	aboutTexture.loadFromFile("../images/about.png");
	backgroundTexture.loadFromFile("../images/Penguins.jpg");

	Sprite menuSprite1(menuTexture1), menuSprite2(menuTexture2), menuSprite3(menuTexture3), aboutSprite(aboutTexture), backgroundSprite(backgroundTexture);

	bool isMenu = true;
	int menuNum = 0;
	menuSprite1.setPosition(100, 30);
	menuSprite2.setPosition(100, 90);
	menuSprite3.setPosition(100, 150);
	backgroundSprite.setPosition(345, 0);

	while (isMenu) {
		menuSprite1.setColor(Color::White);
		menuSprite2.setColor(Color::White);
		menuSprite3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menuSprite1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menuSprite2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menuSprite3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
			switch (menuNum) {
				case 1: isMenu = false; break;
				case 2:  {
					window.draw(aboutSprite);
					window.display();
					while (!Keyboard::isKeyPressed(Keyboard::Escape));
					break;
				}
				case 3: window.close(); isMenu = false; break;
			}

		window.draw(backgroundSprite);
		window.draw(menuSprite1);
		window.draw(menuSprite2);
		window.draw(menuSprite3);

		window.display();
	}
}