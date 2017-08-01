#include <iostream>
#include <SFML/Graphics.hpp>
#include <map.h>
#include <view.h>
#include <mission.h>
#include <cmath>

using namespace sf;
using namespace std;



class Player {
private: float x, y;
public:
	float width, height, dX, dY, speed;
	int score, health;
	bool life, isMove, isSelect, onGround;
	enum {left, right, up, down, jump, stay} state;
	String file;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String filePath, float x, float y, float width, float height) {
		dX = 0; dY = 0; speed = 0; score = 0; health = 100;
		life = true; isMove = false; isSelect = false, onGround = false, state = stay;
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
	void update(float time) {
		control();
		switch (state) {
			case right: dX = speed; break;
			case left: dX = -speed; break;
			case up: break;
			case down: break;
			case jump: break;
			case stay: break;

		}
		x += dX * time;
		checkCollisionWithMap(dX, 0);
		y += dY * time;
		checkCollisionWithMap(0, dY);

		if (!isMove) speed = 0;
		sprite.setPosition(x + width / 2 , y + height / 2);
		if (health <= 0) life = false;
		if (!onGround) dY = dY + 0.0015 * time;
	}

	void control() {
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				state = left;
				speed = 0.1;

//				currentFrame += 0.005 * time;
//				if (currentFrame > 3) currentFrame = 0;
//				p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 96, 96, 96));
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				state = right;
				speed = 0.1;

//				currentFrame += 0.005 * time;
//				if (currentFrame > 3) currentFrame = 0;
//				p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 192, 96, 96));
			}
			if (Keyboard::isKeyPressed(Keyboard::Up) && onGround) {
				state = jump; dY = -1; onGround = false;
//				currentFrame += 0.005 * time;
//				if (currentFrame > 3) currentFrame = 0;
//				p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 307, 96, 96));
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				state = down;
				speed = 0.1;
//				currentFrame += 0.005 * time;
//				if (currentFrame > 3) currentFrame = 0;
//				p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 0, 96, 96));
			}
	}

	void checkCollisionWithMap(float accelX, float accelY) {
		for (int i = (int)(y / 32); i < (y + height) / 32; ++i) {
			for (int j = (int)(x / 32); j < (x + width) / 32; ++j) {
				if (tileMap[i][j] == '0') {
					if (accelY > 0) {
						y = i * 32 - height;
						onGround = true;}
					if (accelY < 0) {
						y = i * 32 + 32;
						accelY = 0;}
					if (accelX > 0) x = j * 32 - width;
					if (accelX < 0) x = j * 32 + 32;
				}else onGround = false;
			}
		}
	}

	float getPlayerCoordinateX() { return x; }
	float getPlayerCoordinateY() { return y; }
	void setPlayerCoordinateX(float x) { this->x = x; }
	void setPlayerCoordinateY(float y) { this->y = y; }

};

int main() {
	RenderWindow window(VideoMode(1366, 768), "SMFL works!");
	view.reset(FloatRect(0, 0, 1024, 768));
	Clock clock;
	Clock gameTimeClock;
	int gameTime = 0;
	float currentFrame = 0;

	Image mapImage;
	mapImage.loadFromFile("../images/map.png");
	Texture mapTexture;
	mapTexture.loadFromImage(mapImage);
	Sprite mapSprite;
	mapSprite.setTexture(mapTexture);

	Player p("hero.png", 250, 500, 96, 54);

	Font font;
	font.loadFromFile("../fonts/CyrilicOld.TTF");
	Text text("", font, 20);
	text.setColor(Color::Black);

	bool showMissionText = true;
	Image questImage;
	questImage.loadFromFile("../images/missionbg.jpg");
	questImage.createMaskFromColor(Color(0, 0, 0));
	Texture questTexture;
	questTexture.loadFromImage(questImage);
	Sprite questSprite;
	questSprite.setTexture(questTexture);
	questSprite.setTextureRect(IntRect(0, 0, 340, 510));
	questSprite.setScale(0.6f, 0.6f);


	int tempX = 0;
	int tempY = 0;
	float distance = 0;


	while (window.isOpen()) {


		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 500;

		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);


		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Tab) {
					switch (showMissionText){
						case true: {
							text.setString("Health : " + to_string(p.health) + "\n" + getTextMission(getCurrentMission((int)p.getPlayerCoordinateX())));
							showMissionText = false;
							break;
						}
						case false:
							text.setString("");
							showMissionText = true;
							break;
					}
				}
			if (event.type == Event::MouseButtonPressed) {
				if (event.key.code == Mouse::Left)
					if (p.sprite.getGlobalBounds().contains(pos.x, pos.y)) {
						p.sprite.setColor(Color::Green);
						p.isSelect = true;
					}

				if (p.isSelect)
					if (event.key.code == Mouse::Right) {
						p.isMove = true;
						p.isSelect = false;
						p.sprite.setColor(Color::White);
						tempX = pos.x;
						tempY = pos.y;
						float dX = pos.x - p.getPlayerCoordinateX();
						float dY = pos.y - p.getPlayerCoordinateY();
						float rotation = (float)((atan2(dY, dX)) / M_PI * 180);
						cout << rotation << endl;
						p.sprite.setRotation(rotation);
					}
			}
		}

		if (p.isMove) {
			distance = (float)sqrt(pow(tempX - p.getPlayerCoordinateX(), 2) + pow(tempY - p.getPlayerCoordinateY(), 2));

			if (distance > 2) {
				p.setPlayerCoordinateX((float)(p.getPlayerCoordinateX() + 0.1 * time *(tempX - p.getPlayerCoordinateX()) / distance));
				p.setPlayerCoordinateY((float)(p.getPlayerCoordinateY() + 0.1 * time *(tempY - p.getPlayerCoordinateY()) / distance));

			}else
				p.isMove = false;
		}

		if (p.life) setPlayerCoordinatesForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());

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