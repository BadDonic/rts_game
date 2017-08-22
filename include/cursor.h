#ifndef COURSEWORK_CURSOR_H
#define COURSEWORK_CURSOR_H

#include <SFML/Graphics.hpp>
#include <list>
#include <building.h>

enum {CommandCenter, Barrack, SupplyDepot, Default, Mineral, Gas};

using namespace sf;
using namespace std;

class Cursor {
	bool click;
	bool correctPlace;
	RectangleShape rectangle;
	int type;
	Image defaultImage;
	Image * buildingsImage;
	Texture texture;
	Sprite sprite;
	bool checkCorrectPlace(RenderWindow &window, list<Building *> * buildingList);
public:
	Cursor(Image * buildingImage);
	void setCursorPosition(Vector2f position);
	bool isClicked();
	void setClick(bool click);
	void setCursorType(int type);
	int getType();
	void drawCursor(RenderWindow &window, list<Building *> *buildingList);
	void setRectanglePosition(Vector2f position);
	void setRectangleSize(Vector2f size);
	void drawRectangle(RenderWindow &window);
	bool getCorrectPlace();
	FloatRect getRect();
	Vector2f getPosition();
};


#endif //COURSEWORK_CURSOR_H
