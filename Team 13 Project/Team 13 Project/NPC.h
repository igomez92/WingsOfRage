#ifndef NON_PLAYER_CHARACTER_H
#define NON_PLAYER_CHARACTER_H

#include <string>
#include "Character.h"

// A Nonplayer Character is a type of Characeter that isn't an enemy.  NPC won't normally attack you, but will fight enemies.
class NPC : public Character
{
public:
	NPC();

	NPC(int xPos, int yPos, Direction startDir, Animation animationToUse, 
		unsigned int mHealth, unsigned int startAttack, std::string name);

	NPC(int savedX, int savedY, Direction savedDir, Animation savedAnimation, unsigned int savedCurrentHealth, 
		unsigned int savedMaxHealth, unsigned int savedAttack, unsigned int savedLevel, std::string savedName);

	~NPC();

private:
	std::string npcName;
};

#endif