#ifndef PLAYER_H
#define PLAYER_H

#include "VisibleObject.h"

class Player : public VisibleObject
{
public:
	Player(std::string file, int x, int y);
	~Player();

	void update();
	int xPos;
	int yPos;

private:
	unsigned int health;
	unsigned int level;
};

#endif