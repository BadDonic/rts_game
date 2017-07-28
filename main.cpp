#include <iostream>
#include <SFML/Graphics.hpp>
#include <map.h>

using namespace sf;

class Player {
public:
	float x, y, width, height, accelX, accelY, speed;
	int dir;
	String file;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String filePath, float x, float y, float width, float height) {
		accelX = 0; accelY = 0; speed = 0; dir = 0;
		file = filePath;
		this->width = width;
		this->height = height;
		this->x = x;
		this->y = y;
		image.loadFromFile("../images/" + file);
		image.createMaskFromColor(Color(41, 33, 59));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, this->width, this->height));
	}
	void update(float time) {
		switch (dir) {
			case 0: accelX = speed; accelY = 0; break;
			case 1: accelX = -speed; accelY = 0; break;
			case 2: accelX = 0; accelY = speed; break;
			case 3: accelX = 0; accelY = -speed; break;
		}
		x += accelX * time;
		y += accelY * time;

		speed = 0;
		sprite.setPosition(x , y);
	}
};

int main() {
	RenderWindow window(VideoMode(640, 480), "SMFL works!");
	Clock clock;
	float currentFrame = 0;

	Image mapImage;
	mapImage.loadFromFile("../images/map.png");
	Texture mapTexture;
	mapTexture.loadFromImage(mapImage);
	Sprite mapSprite;
	mapSprite.setTexture(mapTexture);

	Player p("hero.png", 250, 250, 96, 96);

	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 500;


		Event event;
		while (window.pollEvent(event)) if (event.type == Event::Closed) window.close();

		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			p.dir = 1; p.speed = 0.1;
			currentFrame += 0.005 * time;
			if (currentFrame > 3) currentFrame = 0;
			p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 96, 96, 96));
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			p.dir = 0; p.speed = 0.1;
			currentFrame += 0.005 * time;
			if (currentFrame > 3) currentFrame = 0;
			p.sprite.setTextureRect(IntRect(96 * int(currentFrame),192, 96, 96));
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			p.dir = 3; p.speed = 0.1;
			currentFrame += 0.005 * time;
			if (currentFrame > 3) currentFrame = 0;
			p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 288, 96, 96));
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			p.dir = 2; p.speed = 0.1;
			currentFrame += 0.005 * time;
			if (currentFrame > 3) currentFrame = 0;
			p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 0, 96, 96));
		}
		p.update(time);
		window.clear();
		for (int i = 0; i < HEIGHT_MAP; ++i) {
			for (int j = 0; j < WIDTH_MAP; ++j) {
				if (tileMap[i][j] == ' ') mapSprite.setTextureRect(IntRect(0, 0, 32, 32));
				if (tileMap[i][j] == 's') mapSprite.setTextureRect(IntRect(32, 0, 32, 32));
				if (tileMap[i][j] == '0') mapSprite.setTextureRect(IntRect(64, 0, 32, 32));

				mapSprite.setPosition(j * 32, i * 32);
				window.draw(mapSprite);
			}
		}
		window.draw(p.sprite);
		window.display();
	}

	return EXIT_SUCCESS;
}