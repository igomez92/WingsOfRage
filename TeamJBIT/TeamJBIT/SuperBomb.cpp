#include "SuperBomb.h"


SuperBomb::SuperBomb(void)
	:hasFinished(false), runTime(0.5f), damDone(false)
{
}


SuperBomb::~SuperBomb(void)
{
}

void SuperBomb::update(float deltaTime)
{
	// Do some sort of update for the animated sprite
}

void SuperBomb::draw()
{
	// Draw the animated sprite
}

void SuperBomb::checkForDestruction(Enemy& enemy)
{
	// If the enemy isn't a boss
	if(enemy.type != Boss)
	{
		// Kill it
		enemy.takeDam(10000);
	}
	else
	{
		enemy.takeDam(100);
	}

	damDone = true;
}

void SuperBomb::finishedDamagePhase()
{
	hasFinished = true;
}