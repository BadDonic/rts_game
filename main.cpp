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
	float width, height, accelX, accelY, speed;
	int dir, score, health;
	bool life, isMove, isSelect;
	String file;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String filePath, float x, float y, float width, float height) {
		accelX = 0; accelY = 0; speed = 0; dir = 0; score = 0; health = 100;
		life = true; isMove = false; isSelect = false;
		file = filePath;
		this->width = width;
		this->height = height;
		this->x = x;
		this->y = y;
		image.loadFromFile("../images/" + file);
		image.createMaskFromColor(Color(0, 0, 255));
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
		interactionWithMap();
		sprite.setPosition(x , y);
		sprite.setOrigin(width / 2, height / 2);
		if (health <= 0) life = false;
	}

	void interactionWithMap() {
		for (int i = (int)(y / 32); i < (y + height) / 32; ++i) {
			for (int j = (int)(x / 32); j < (x + width) / 32; ++j) {
				if (tileMap[i][j] == '0') {
					if (accelY > 0) y = i * 32 - height;
					if (accelY < 0) y = i * 32 + 32;
					if (accelX > 0) x = j * 32 - width;
					if (accelX < 0) x = j * 32 + 32;
					return;
				}
				if (tileMap[i][j] == 's') {
					score++;
					tileMap[i][j] = ' ';
				}
				if (tileMap[i][j] == 'h') {
					health += 20;
					tileMap[i][j] = ' ';
				}
				if (tileMap[i][j] == 'f') {
					health -= 40;
					tileMap[i][j] = ' ';
				}
			}
		}
	}

	float getPlayerCoordinateX() { return x; }
	float getPlayerCoordinateY() { return y; }
	void setPlayerCoordinateX(float x) { this->x = x; }
	void setPlayerCoordinateY(float y) { this->y = y; }

};

int main() {
	RenderWindow window(VideoMode(1366, 768), "SMFL works!", Style::Fullscreen);
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

	Player p("heroForRotate.png", 250, 250, 136, 74);

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

	int randomGenerateTimer = 3000;

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

		randomGenerateTimer += time;
		if (randomGenerateTimer > 3000) {
			randomMapGenerate();
			randomGenerateTimer = 0;
		}

		if (p.life) {
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				p.dir = 1;
				p.speed = 0.1;
				currentFrame += 0.005 * time;
				if (currentFrame > 3) currentFrame = 0;
				p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 96, 96, 96));
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				p.dir = 0;
				p.speed = 0.1;
				currentFrame += 0.005 * time;
				if (currentFrame > 3) currentFrame = 0;
				p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 192, 96, 96));
			}
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				p.dir = 3;
				p.speed = 0.1;
				currentFrame += 0.005 * time;
				if (currentFrame > 3) currentFrame = 0;
				p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 307, 96, 96));
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				p.dir = 2;
				p.speed = 0.1;
				currentFrame += 0.005 * time;
				if (currentFrame > 3) currentFrame = 0;
				p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 0, 96, 96));
			}
			//setPlayerCoordinatesForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
		}else {
			view.move(0.1, 0);
		}



		Vector2i localPosition = Mouse::getPosition(window);
		if (localPosition.x < 3) view.move(-0.2 * time, 0);
		if (localPosition.x > window.getSize().x - 73) view.move(0.2 * time, 0);
		if (localPosition.y > window.getSize().y - 58) view.move(0, 0.2 * time);
		if (localPosition.y < 3) view.move(0, -0.2 * time);


		p.update(time);

		window.setView(view);
		window.clear();

		if (getCurrentMission(p.getPlayerCoordinateX()) == 0) {
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
		}
		if (getCurrentMission(p.getPlayerCoordinateX()) == 1) {
			for (int i = 0; i < HEIGHT_MAP; ++i) {
				for (int j = 0; j < WIDTH_MAP; ++j) {
					if (tileMap[i][j] == ' ') mapSprite.setTextureRect(IntRect(64, 0, 32, 32));
					if (tileMap[i][j] == 's') mapSprite.setTextureRect(IntRect(32, 0, 32, 32));
					if (tileMap[i][j] == '0') mapSprite.setTextureRect(IntRect(0, 0, 32, 32));
					if (tileMap[i][j] == 'f') mapSprite.setTextureRect(IntRect(96, 0, 32, 32));
					if (tileMap[i][j] == 'h') mapSprite.setTextureRect(IntRect(128, 0, 32, 32));

					mapSprite.setPosition(j * 32, i * 32);
					window.draw(mapSprite);
				}
			}
		}
		if (!showMissionText) {
			text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);
			questSprite.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);
			window.draw(questSprite); window.draw(text);
		}

		window.draw(p.sprite);
		window.display();
	}

	return EXIT_SUCCESS;
}