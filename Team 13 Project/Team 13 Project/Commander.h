#ifndef COMMANDER_H
#define COMMANDER_H

#include "Character.h"
#include "Status.h"
#include <string>

// A commander is a type of Character.  The player will choose a commander to play as.
class Commander : public Character
{
public:
	Commander();
	Commander(int xPos, int yPos, Direction startDir, Animation animationToUse, 
		unsigned int mHealth, unsigned int startAttack, std::string name);
	Commander(int savedX, int savedY, Direction savedDir, Animation savedAnimation, unsigned int savedCurrentHealth, 
		unsigned int savedMaxHealth, unsigned int savedAttack, unsigned int savedLevel, std::string savedName);
	~Commander();

private:
	std::string playerName;
};

#endif // COMMANDER_H