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
	Texture texture;
	Sprite sprite;
	String name;
	Entity (Image &image, float &x, float &y, int &width, int &height, String &name) {
		this->x = x; this->y = y;
		this->width = width; this->height = height; 	this->name = name;
		dx = 0; dy = 0;
		moveTimer = 0;speed = 0; health = 100;
		life = true; onGround = false; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(width / 2, height / 2);
	}
};

class Player : public Entity {
public:
	enum {left, right, up, down, jump, stay} state;
	int score;

	Player(Image &image, float x, float y, int width, int height, String name) : Entity(image, x, y, width, height, name) {
		score = 0; state = stay;
		if ( name == "Player1") sprite.setTextureRect(IntRect(4, 19, width, height));
	}

	void control() {
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left; speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right; speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up) && onGround) {
			state = jump; dy = -1; onGround = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			state = down; speed = 0.1;
		}
	}

	void checkCollisionWithMap(float dx, float dy) {
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
				}
			}
		}
	}

	void update(float time) {
		control();
		switch (state) {
			case right: dx = speed; break;
			case left: dx = -speed; break;
			case up: break;
			case down: dx = 0; break;
			case jump: break;
			case stay: break;

		}
		x += dx * time;
		checkCollisionWithMap(dx, 0);
		y += dy * time;
		checkCollisionWithMap(0, dy);
		sprite.setPosition(x + width / 2 , y + height / 2);
		if (health <= 0) life = false;
		else setPlayerCoordinatesForView(x, y);
		if (!isMove) speed = 0;
		dy = dy + (float)0.0015 * time;
	}
};

class Enemy : public Entity {
public:
	Enemy(Image &image, float x, float y, int width, int height, String name) : Entity(image, x, y, width, height, name) {
		if (name == "EasyEnemy") {
			sprite.setTextureRect(IntRect(0, 0, width, height));
			dx = 0.1;
		}
	}

	void checkCollisionWithMap(float dx, float dy) {
		for (int i = (int) (y / 32); i < (y + height) / 32; ++i) {
			for (int j = (int) (x / 32); j < (x + width) / 32; ++j) {
				if (tileMap[i][j] == '0') {
					if (dy > 0) y = i * 32 - height;
					if (dy < 0) y = i * 32 + 32;
					if (dx > 0) {
						x = j * 32 - width;
						dx = -0.1;
						sprite.scale(-1, 1);
					}
					if (dx < 0) {
						x = j * 32 + 32;
						dx = 0.1;
						sprite.scale(-1, 1);
					}
				}
			}
		}
	}

	void update(float time) {
		if (name == "EasyEnemy") {
			x += dx * time;
			checkCollisionWithMap(dx, 0);
			sprite.setPosition(x + width / 2, y + height / 2);
			if (health <= 0) life = false;
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

	Image heroImage;
	heroImage.loadFromFile("../images/MilesTailsPrower.gif");
	Player hero(heroImage, 750, 500, 40, 30, "Player1");

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("../images/shamaich.png");
	easyEnemyImage.createMaskFromColor(Color(255, 0, 0));
	Enemy easyEnemy(easyEnemyImage, 850, 671, 200, 97, "EasyEnemy");

	Clock clock;
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time /= 500;

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
		}

		hero.update(time);
		easyEnemy.update(time);

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

		window.draw(easyEnemy.sprite);
		window.draw(hero.sprite);
		window.display();
	}
	return EXIT_SUCCESS;
}
#pragma clang diagnostic pop