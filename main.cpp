#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <view.h>
#include <level.h>
#include <vector>
#include <list>
#include <lifeBar.h>

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
	enum {left, right, up, down, jump, stay, rightTop} state;
	int score;

	Player(Image &image, String name, Level &level, float x, float y, int width, int height) : Entity(image, name, x, y, width, height) {
		score = 0; state = stay; obj = level.GetAllObjects();
		if ( name == "Player1") sprite.setTextureRect(IntRect(4, 19, width, height));
	}

	void control() {
		if (Keyboard::isKeyPressed(Keyboard::Left)) { state = left; speed = 0.1; }
		if (Keyboard::isKeyPressed(Keyboard::Right)) { state = right; speed = 0.1; }
		if (Keyboard::isKeyPressed(Keyboard::Up) && onGround) { state = jump; dy = -1; onGround = false; }
		if (Keyboard::isKeyPressed(Keyboard::Down)) { state = down; speed = 0.1; }
		if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Up)) state = rightTop;
	}

	void checkCollisionWithMap(float dx, float dy) {
		for (int i = 0; i < obj.size(); ++i) {
			if (getRect().intersects(obj[i].rect))
				if (obj[i].name == "solid") {
					if (dy > 0) {
						y = obj[i].rect.top - height;
						this->dy = 0;
						onGround = true;
					}
					if (dy < 0) {
						y = obj[i].rect.top + obj[i].rect.height;
						this->dy = 0;
					}
					if (dx > 0) { x = obj[i].rect.left - width; }
					if (dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
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
			case rightTop: dx = speed;break;
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

class MovingPlatform : public Entity {
public:
	MovingPlatform(Image &image, String name, Level &lvl, float x, float y, int width, int height) : Entity(image, name, x, y, width, height) {
		sprite.setTextureRect(IntRect(0, 0, width, height));
		dx = 0.08;
	}
	void update(float time) {
		x += dx * time;
		moveTimer += time;
		if (moveTimer > 3000) { dx *= -1; moveTimer = 0; }
		sprite.setPosition(x + width / 2, y + height / 2);
	}
};

class Bullet : public Entity {
public:
	int direction;

	Bullet (Image &image, String name, Level &lvl, float x, float y, int width, int height, int dir) : Entity(image, name, x, y, width,height) {
		obj = lvl.GetObjects("solid");
		direction = dir;
		speed = 0.8;
	}

	void update(float time) {
		switch (direction) {
			case 0: dx = -speed; dy = 0; break;
			case 1: dx = speed; dy = 0; break;
			case 2: dx = 0; dy = -speed; break;
			case 3: dx = 0; dy = -speed; break;
			case 4: dx = 0; dy = -speed; break;
			case 5: dx = 0; dy = -speed; break;
			case 6: dx = speed; dy = -speed; break;
		}

		x += dx * time;
		y += dy * time;

		if (x <= 0) x = 1;
		if (y <= 0) y = 1;

		for (auto &i : obj)
			if (getRect().intersects(i.rect)) life = false;

		sprite.setPosition(x + width / 2, y + height / 2);
	}
};

int main() {
	RenderWindow window(VideoMode(640, 480), "CourseWork!!!");
	view.reset(FloatRect(0, 0, 480, 640));

	Level lvl;
	lvl.LoadFromFile("../images/map.tmx");

	LifeBar lifeBarPlayer;

	SoundBuffer shootBuffer;
	shootBuffer.loadFromFile("../sound/shoot.ogg");
	Sound shootSound;
	shootSound.setBuffer(shootBuffer);

	Music music;
	music.openFromFile("../sound/Something_Just_Like_This.ogg");
	music.play();

	Image heroImage;
	heroImage.loadFromFile("../images/MilesTailsPrower.gif");
	heroImage.createMaskFromColor(Color::Black);
	Object heroObj = lvl.GetObject("player");

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("../images/shamaich.png");
	easyEnemyImage.createMaskFromColor(Color::Red);
	vector<Object> objs = lvl.GetObjects("easyEnemy");

	Image movingPlatformImage;
	movingPlatformImage.loadFromFile("../images/movingPlatform.png");
	vector<Object> movingPlatformObjs = lvl.GetObjects("MovingPlatform");

	Image bulletImage;
	bulletImage.loadFromFile("../images/bullet.png");
	bulletImage.createMaskFromColor(Color::Black);

	Player hero(heroImage, "Player1", lvl, heroObj.rect.left, heroObj.rect.top, 40, 30);

	list<Entity *> entities;


	for (auto &obj : objs)
		entities.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, obj.rect.left, obj.rect.top, 200, 97));

	for (auto &obj : movingPlatformObjs)
		entities.push_back(new MovingPlatform(movingPlatformImage, "MovingPlatform", lvl, obj.rect.left, obj.rect.top, 95, 22));

	Clock clock;
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time /= 500;

		Event event = {};
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
			if (event.type == Event::KeyPressed || event.type == Event::KeyReleased)
				if (event.key.code == Keyboard::Space) {
					entities.push_back(new Bullet(bulletImage, "Bullet", lvl, hero.x, hero.y, 16, 16, hero.state));
					shootSound.play();
				}
		}
		lifeBarPlayer.update(hero.health);

		hero.update(time);
		for (auto iter = entities.begin(); iter != entities.end();) {
			Entity * temp = *iter;
			temp->update(time);
			if (!temp->life) {
				iter = entities.erase(iter);
				delete(temp);
			}else iter++;
		}

		for (auto &iter : entities) {
			if (iter->getRect().intersects(hero.getRect())) {
				if (iter->name == "MovingPlatform") {
					if (hero.dy > 0)
						if (hero.y + hero.height < iter->y +  iter->height) {
							hero.y = iter->y - hero.height + 3;
							hero.x += iter->dx * time;
							hero.dy = 0;
							hero.onGround = true;
						}
				}
				if (iter->name == "EasyEnemy")
					if (hero.dy > 0 && !hero.onGround) {
						iter->dx = 0;
						hero.dy = (float) -0.2;
						iter->health = 0;
					} else hero.health -= 0.00000000000005;
			}
			for (auto &iter2 : entities) {
				if (iter->getRect() != iter2->getRect())
					if (iter->getRect().intersects(iter2->getRect())) {
						iter->dx *= -1;
						iter->sprite.scale(-1, 1);
					}
			}
		}


		window.setView(view);
		window.clear(Color(77,83,140));

		lvl.Draw(window);

		for (auto &entity : entities)
			window.draw(entity->sprite);

		lifeBarPlayer.draw(window);
		window.draw(hero.sprite);
		window.display();
	}
	return EXIT_SUCCESS;
}
#pragma clang diagnostic pop