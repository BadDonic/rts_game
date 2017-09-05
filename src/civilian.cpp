#include <cmath>
#include "civilian.h"

Civilian::Civilian(Image &unitImage, Image &healthBarImage, const IntRect &rect, const Vector2f &pos, int health) : Unit(unitImage, healthBarImage, rect, pos, health) {
	sprite.setScale(1.7, 1.7);
	sprite.setOrigin(rect.width / 2, rect.height / 2);
	sprite.setPosition(pos);
	bar.setScale(1, 1);
	rectangle.setSize(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
}

void Civilian::update(float time) {
	float x = sprite.getPosition().x;
	float y = sprite.getPosition().y;

	if (isMove) {
		double distance = sqrt(pow(x - direction.x, 2) + pow(y - direction.y, 2));
		angle = (int)(atan2(direction.y - y, direction.x - x) * 180 / M_PI);
		setRotation(angle);
		setCurrentFrame(time);
		if (distance > 2) {
			x += 0.1 * time * (direction.x - x) / distance;
			y += 0.1 * time * (direction.y - y) / distance;

		}else
			isMove = false;
	}
	sprite.setPosition(x, y);
	bar.setPosition(sprite.getGlobalBounds());
	rectangle.setPosition(sprite.getPosition().x - sprite.getGlobalBounds().width / 2,sprite.getPosition().y - sprite.getGlobalBounds().height / 2 + 2);
}

void Civilian::draw(RenderWindow &window) {
	window.draw(sprite);
	bar.draw(window);
	if (select) window.draw(rectangle);
}

void Civilian::setRotation(int &angle) {
	IntRect rect = sprite.getTextureRect();
	if (angle < 22.5 && angle > -22.5) {
		rect.left = 109;
	}else if (angle < 67.5 &&  angle > 22.5) {
		rect.left = 156;
	}else if (angle < 112.5 &&  angle > 67.5) {
		rect.left = 203;
	}else if (angle < 157.5 &&  angle > 112.5) {
		rect.left = 248;
	}else if (angle > 157.5  ||  angle < -157.5) {
		rect.left = 295;
	}else if (angle < -112.5 &&  angle > -157.5) {
		rect.left = 342;
	}else if (angle < -67.5 &&  angle > -112.5) {
		rect.left = 13;
	}else if (angle < -22.5 &&  angle > -67.5) {
		rect.left = 60;
	}
	sprite.setTextureRect(rect);
}

void Civilian::setCurrentFrame(float &time) {
	currentFrame += 0.005 * time;
	if (currentFrame > 7) currentFrame = 0;
	IntRect rect = sprite.getTextureRect();
	rect.top = 35 * (int)currentFrame;
	sprite.setTextureRect(rect);
}
