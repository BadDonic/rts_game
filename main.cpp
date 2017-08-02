#include <iostream>
#include <SFML/Graphics.hpp>
#include <view.h>
#include <level.h>
#include <vector>
#include <list>

using namespace sf;
using namespace std;

class Entity {
public:
	vector<Object> obj;
	float x, y, dx, dy, speed, moveTimer;
	int width, height, health;
	bool life, isMove, onGround;
	Texture texture;
	Sprite sprite;
	String name;
	Entity (Image &image, String &name, float &x, float &y, int &width, int &height) {
		this->x = x; this->y = y;
		this->width = width; this->height = height; 	this->name = name;
		dx = 0; dy = 0;
		moveTimer = 0;speed = 0; health = 100;
		life = true; onGround = false; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(width / 2, height / 2);
	}

	virtual void update(float time) = 0;

	FloatRect getRect() { return FloatRect(x, y, width, height); }
};

class Player : public Entity {
public:
	enum {left, right, up, down, jump, stay} state;
	int score;

	Player(Image &image, String name, Level &level, float x, float y, int width, int height) : Entity(image, name, x, y, width, height) {
		score = 0; state = stay; obj = level.GetAllObjects();
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
		for (int i = 0; i < obj.size(); ++i) {
			if (getRect().intersects(obj[i].rect)) {
				if (obj[i].name == "solid") {
					if (dy>0)	{ y = obj[i].rect.top - height;  this->dy = 0; onGround = true; }
					if (dy<0)	{ y = obj[i].rect.top + obj[i].rect.height;   this->dy = 0; }
					if (dx>0)	{ x = obj[i].rect.left - width; }
					if (dx<0)	{ x = obj[i].rect.left + obj[i].rect.width; }
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
	Enemy(Image &image, String name, Level &level, float x, float y, int width, int height) : Entity(image, name, x, y, width, height) {
		obj = level.GetObjects("solid");
		if (name == "EasyEnemy") {
			sprite.setTextureRect(IntRect(0, 0, width, height));
			dx = 0.1;
		}
	}

	void checkCollisionWithMap(float dx, float dy) {
		for (int i = 0; i < obj.size(); ++i) {
			if (getRect().intersects(obj[i].rect)) {
				if (dy > 0) y = obj[i].rect.top - height;
				if (dy < 0) y = obj[i].rect.top + obj[i].rect.height;
				if (dx > 0) { x = obj[i].rect.left - width; this->dx = -0.1; sprite.scale(-1, 1); }
				if (dx < 0) {
					x = obj[i].rect.left+ obj[i].rect.width; this->dx = 0.1; sprite.scale(-1, 1); }
			}
		}
	}

	void update(float time) {
		if (name == "EasyEnemy") {
			checkCollisionWithMap(dx, 0);
			x += dx * time;
			sprite.setPosition(x + width / 2, y + height / 2);
			if (health <= 0) life = false;
		}
	}

};


int main() {
	RenderWindow window(VideoMode(640, 480), "CourseWork!!!");
	view.reset(FloatRect(0, 0, 480, 640));

	Level lvl;
	lvl.LoadFromFile("../images/map.tmx");

	Image heroImage;
	heroImage.loadFromFile("../images/MilesTailsPrower.gif");
	heroImage.createMaskFromColor(Color::Black);
	Object heroObj = lvl.GetObject("player");


	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("../images/shamaich.png");
	easyEnemyImage.createMaskFromColor(Color::Red);

	Player hero(heroImage, "Player1", lvl, heroObj.rect.left, heroObj.rect.top, 40, 30);


	list<Entity *> entities;

	vector<Object> objs = lvl.GetObjects("easyEnemy");

	for (auto &obj : objs)
		entities.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, obj.rect.left, obj.rect.top, 200, 97));

	Clock clock;
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time /= 500;

		Event event = {};
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
		}

		hero.update(time);
		for (auto iter = entities.begin(); iter != entities.end();) {
			Entity * temp = *iter;
			temp->update(time);
			if (!temp->life) {
				iter = entities.erase(iter);
				delete(temp);
			}else iter++;
		}

		for (auto iter = entities.begin(); iter != entities.end(); iter++) {
			if ((*iter)->getRect().intersects(hero.getRect()))
				if ((*iter)->name == "EasyEnemy")
					if (hero.dy > 0 && !hero.onGround) {
						(*iter)->dx = 0;
						hero.dy = -0.2;
						(*iter)->health = 0;
					}else hero.health -= 5;
		}


		window.setView(view);
		window.clear(Color(77,83,140));

		lvl.Draw(window);

		for (auto &entity : entities)
			window.draw(entity->sprite);

		window.draw(hero.sprite);
		window.display();
	}
	return EXIT_SUCCESS;
}
#pragma clang diagnostic pop