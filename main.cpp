#include <iostream>
#include <SFML/Graphics.hpp>
#include <map.h>
#include <view.h>
#include <mission.h>
#include <cmath>

using namespace sf;
using namespace std;

class Entity {
public:
	float x, y, dx, dy, speed, moveTimer;
	int width, height, health;
	bool life, isMove, onGround;
};

class Player {
public:
	float x, y, width, height, dx, dy, speed;
	int score, health;
	bool life, isMove, onGround;
	enum {left, right, up, down, jump, stay} state;
	String file;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String filePath, float x, float y, float width, float height) {
		dx = 0; dy = 0; speed = 0; score = 0; health = 100;
		life = true; isMove = false; onGround = false, state = stay;
		file = filePath;
		this->width = width;
		this->height = height;
		this->x = x;
		this->y = y;
		image.loadFromFile("../images/" + file);
		image.createMaskFromColor(Color(0, 0, 255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 134, this->width, this->height));
		sprite.setOrigin(width / 2, height / 2);

	}

	void control() {
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left;
			speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right;
			speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up) && onGround) {
			state = jump; dy = -1; onGround = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			state = down;
			speed = 0.1;
		}
	}

	void update(float time) {
		control();
		switch (state) {
			case right: dx = speed; break;
			case left: dx = -speed; break;
			case up: break;
			case down: break;
			case jump: break;
			case stay: break;

		}
		x += dx * time;
		checkCollisionWithMap(dx);
		y += dy * time;
		checkCollisionWithMap(0, dy);
		if (!isMove) speed = 0;
		sprite.setPosition(x + width / 2 , y + height / 2);
		if (health <= 0) life = false;
		else setPlayerCoordinatesForView(x, y);
		dy = dy + 0.0015 * time;
	}

	void checkCollisionWithMap(float dx, float dy = 0) {
		for (int i = (int) (y / 32); i < (y + height) / 32; ++i) {
			for (int j = (int) (x / 32); j < (x + width) / 32; ++j) {
				if (tileMap[i][j] == '0') {
					if (dy > 0) {
						y = i * 32 - height;
						onGround = true;
						this->dy = 0;
					}
					if (dy < 0) {
						y = i * 32 + 32;
						this->dy = 0;
					}
					if (dx > 0) x = j * 32 - width;
					if (dx < 0) x = j * 32 + 32;
				} else onGround = false;
			}
		}
	}
};

int main() {
	RenderWindow window(VideoMode(1366, 768), "CourseWork!!!");
	view.reset(FloatRect(0, 0, 1024, 768));


	Image mapImage;
	mapImage.loadFromFile("../images/map.png");
	Texture mapTexture;
	mapTexture.loadFromImage(mapImage);
	Sprite mapSprite;
	mapSprite.setTexture(mapTexture);

	Player p("hero.png", 250, 500, 96, 54);


	Clock clock;
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time /= 500;

		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);


		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
		}

		p.update(time);

		window.setView(view);
		window.clear();

		for (int i = 0; i < HEIGHT_MAP; ++i) {
			for (int j = 0; j < WIDTH_MAP; ++j) {
				if (tileMap[i][j] == ' ') mapSprite.setTextureRect(IntRect(0, 0, 32, 32));
				if (tileMap[i][j] == 's') mapSprite.setTextureRect(IntRect(32, 0, 32, 32));
				if (tileMap[i][j] == '0') mapSprite.setTextureRect(IntRect(64, 0, 32, 32));
				if (tileMap[i][j] == 'f') mapSprite.setTextureRect(IntRect(96, 0, 32, 32));
				if (tileMap[i][j] == 'h') mapSprite.setTextureRect(IntRect(128, 0, 32, 32));

				mapSprite.setPosition(j * 32, i * 32);
				window.draw(mapSprite);
			}
		}

		window.draw(p.sprite);
		window.display();
	}
	return EXIT_SUCCESS;
}