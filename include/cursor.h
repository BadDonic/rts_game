//
// Created by daniel on 08.08.17.
//

#ifndef COURSEWORK_CURSOR_H
#define COURSEWORK_CURSOR_H

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Cursor {
	Image defaultImage;
	Texture texture;
	Sprite sprite;
public:
	Cursor();
	void setCursorPosition(Vector2f position);
	void draw(RenderWindow &window);
};


#endif //COURSEWORK_CURSOR_H
