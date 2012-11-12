#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "Status.h"

// An enemy is a type of Character.  All Enemy types branch from this class
class Enemy : public Character
{
public:
	// Constructs a default Enemy object
	Enemy(int xPosition, int yPosition, int initialHealth, int initialLevel, int initialAttack);
	// Destroys any dynamically-allocated pointers.  Can be removed if unnecessary
	~Enemy();

private:
	// We may need to add additional members here
	int level;
};

#endif // ENEMY_H