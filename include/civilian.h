#ifndef COURSEWORK_CIVILIAN_H
#define COURSEWORK_CIVILIAN_H


#include "unit.h"

class Civilian : public Unit{
public:
	Civilian(Image &unitImage, Image &healthBarImage,const IntRect &rect, const Vector2f &pos, int health);
	void update(float time, const Vector2f &mousePos) override;
	void draw(RenderWindow &window) override;
};


#endif
