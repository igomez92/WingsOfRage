#include "Enemy.h"
// The enemy class contains all the info every enemy will contain.
// Create new enemies that branch from this class

// Creates an enemy object, holding an x Position, y Position, initial health, initial level and initial attack
Enemy::Enemy(int xPosition, int yPosition, int initialHealth, int initialLevel, int initialAttack)
	:Character(xPosition, yPosition, initialHealth, initialAttack), level(initialLevel)
{

}

// Just in case we need to destroy any dynamically-allocated pointers.  Can be removed later
Enemy::~Enemy()
{

}