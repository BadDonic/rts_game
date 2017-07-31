#include <SFML/Graphics.hpp>

using namespace sf;

const int HEIGHT_MAP = 25;
const int WIDTH_MAP = 40;

String tileMap[HEIGHT_MAP] =  {
		"0000000000000000000000000000000000000000",
		"0       s                              0",
		"0   s                                  0",
		"0     s   s                            0",
		"0  s                                   0",
		"0                                      0",
		"0   s     s                            0",
		"0                h                     0",
		"0                                      0",
		"0                                      0",
		"0                          h           0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                           f          0",
		"0             f                        0",
		"0                                      0",
		"0                                      0",
		"0                            f         0",
		"0                                      0",
		"0                                      0",
		"0        f                             0",
		"0                                      0",
		"0000000000000000000000000000000000000000",
};

void randomMapGenerate() {
	int xRandomElement = 0;
	int yRandomElement = 0;
	int countStone = 2;
	srand((unsigned int)time(0));

	while (countStone > 0 ) {
		xRandomElement = 1 + rand() % (WIDTH_MAP - 1);
		yRandomElement = 1 + rand() % (HEIGHT_MAP - 1);

		if (tileMap[yRandomElement][xRandomElement] == ' ') {
			tileMap[yRandomElement][xRandomElement] = 's';
			countStone--;
		}
	}
}