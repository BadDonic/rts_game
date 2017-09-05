#ifndef COURSEWORK_CIVILIAN_H
#define COURSEWORK_CIVILIAN_H


#include <unit.h>

class Civilian : public Unit{
	void setRotation(int &angle);
	void setCurrentFrame(float &time);
public:
	Civilian(Image &unitImage, Image &healthBarImage,const IntRect &rect, const Vector2f &pos, int health);
	void update(float time) override;
	void draw(RenderWindow &window) override;
};


#endif
