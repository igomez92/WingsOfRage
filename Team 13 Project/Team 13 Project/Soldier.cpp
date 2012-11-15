#include "Soldier.h"

Soldier::Soldier()
	:Commander()
{}

Soldier::Soldier(int xPos, int yPos, Direction startDir, Animation animationToUse, 
	unsigned int mHealth, unsigned int startAttack, std::string name)
	:Commander(xPos, yPos, startDir, animationToUse, mHealth, startAttack, name)
{}

Soldier::Soldier(int savedX, int savedY, Direction savedDir, Animation savedAnimation, unsigned int savedCurrentHealth, 
		unsigned int savedMaxHealth, unsigned int savedAttack, unsigned int savedLevel, std::string savedName)
		:Commander(savedX, savedY, savedDir, savedAnimation, savedCurrentHealth, savedMaxHealth, savedAttack, savedLevel,savedName)
{}

Soldier::~Soldier()
{}