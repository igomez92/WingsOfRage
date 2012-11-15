#include "Commander.h"

Commander::Commander()
		:Character()
{
}

Commander::Commander(int xPos, int yPos, Direction startDir, Animation animationToUse, 
		unsigned int mHealth, unsigned int startAttack, std::string name)
		:Character(xPos, yPos, startDir, animationToUse, mHealth, startAttack), playerName(name)
{}

Commander::Commander(int savedX, int savedY, Direction savedDir, Animation savedAnimation, unsigned int savedCurrentHealth, 
		unsigned int savedMaxHealth, unsigned int savedAttack, unsigned int savedLevel, std::string savedName)
		:Character(savedX, savedY, savedDir, savedAnimation, savedCurrentHealth, savedMaxHealth, savedAttack, savedLevel), playerName(savedName)
{}

Commander::~Commander()
{}