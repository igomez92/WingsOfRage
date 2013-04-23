#pragma once
#include "AnimSprite.h"
#include "Enemy.h"

class SuperBomb
{
public:
	SuperBomb(void);
	~SuperBomb(void);

	void update(float deltaTime);
	void draw();

	void checkForDestruction(Enemy& enemy);
	void finishedDamagePhase();
	bool hasFinished;
	bool damDone;
	float runTime;

private:
	AnimSprite sprite;
};

