#ifndef NON_PLAYER_CHARACTER_H
#define NON_PLAYER_CHARACTER_H

#include "Character.h"

// A Nonplayer Character is a type of Characeter that isn't an enemy.  NPC won't normally attack you, but will fight enemies.
class NPC : public Character
{
public:
	// Constructs a default NPC
	NPC(int initialX, int initialY, int initialHealth, int initialAttack, bool isAttackable);
	// Destroys any dynamically-allocated pointers
	~NPC();
private:
	// We will need to add functions here
	bool attackable;
};

#endif