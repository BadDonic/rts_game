//
// Created by daniel on 21.08.17.
//

#ifndef COURSEWORK_CIVILIAN_H
#define COURSEWORK_CIVILIAN_H


#include "unit.h"

class Civilian : public Unit{
public:
	Civilian(Image &unitImage, Image &healthBarImage,const IntRect &rect, const Vector2f &pos, int health);
	void update(float time) override;
	void draw(RenderWindow &window) override;
};


#endif
