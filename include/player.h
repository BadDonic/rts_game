#ifndef COURSEWORK_PLAYER_H
#define COURSEWORK_PLAYER_H


#include "resource.h"

class Player {
	Resource crystal;
	Resource gas;
	Resource unit;
	Player(String crystalImagePath, String gasImagePath, String unitImagePath);
};


#endif //COURSEWORK_PLAYER_H
