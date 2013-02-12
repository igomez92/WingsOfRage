#pragma once

#include "VisibleObject.h"

class Enemy : public VisibleObject
{
public:
	Enemy(std::string file, int x, int y);
	~Enemy(void);

	void update();

	bool continueDraw;
	int xPos;
	int yPos;
};

