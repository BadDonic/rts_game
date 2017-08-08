#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Resource {
	int number;
	int max;
	Image image;
	Texture texture;
	Sprite sprite;
public:
	Resource(String filePath, int max, int x, int y, int width, int height);
	void draw(RenderWindow &window, Font &font, int posX, int posY);
	void setScale(float factorX, float factorY);
};
