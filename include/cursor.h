#ifndef COURSEWORK_CURSOR_H
#define COURSEWORK_CURSOR_H

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Cursor {
	bool click;
	RectangleShape rectangle;
	Image defaultImage;
	Texture texture;
	Sprite sprite;
public:
	Cursor();
	void setCursorPosition(Vector2f position);
	void drawCursor(RenderWindow &window);
	void setRectanglePosition(Vector2f position);
	void setRectangleSize(Vector2f size);
	void drawRectangle(RenderWindow &window);
	bool isClicked();
	void setClick(bool click);
};


#endif //COURSEWORK_CURSOR_H
