#ifndef COURSEWORK_CURSOR_H
#define COURSEWORK_CURSOR_H

#include <SFML/Graphics.hpp>

enum {CommandCenter, Barrack, SupplyDepot, Default};

using namespace sf;
using namespace std;

class Cursor {
	bool click;
	RectangleShape rectangle;
	int type;
	Image defaultImage;
	Image * buildingsImage;
	Texture texture;
	Sprite sprite;
public:
	Cursor(Image * buildingImage);
	void setCursorPosition(Vector2f position);
	bool isClicked();
	void setClick(bool click);
	void setCursorType(int type);
	int getType();
	void drawCursor(RenderWindow &window);
	void setRectanglePosition(Vector2f position);
	void setRectangleSize(Vector2f size);
	void drawRectangle(RenderWindow &window);

};


#endif //COURSEWORK_CURSOR_H
