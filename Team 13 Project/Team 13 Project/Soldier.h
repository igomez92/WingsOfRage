#ifndef SOLDIER_H
#define SOLDIER_H

#include "Commander.h"

// A Soldier is one of the player types
class Soldier : public Commander
{
public:
	Soldier();

	Soldier(int xPos, int yPos, Direction startDir, Animation animationToUse, 
		unsigned int mHealth, unsigned int startAttack, std::string name);

	Soldier(int savedX, int savedY, Direction savedDir, Animation savedAnimation, unsigned int savedCurrentHealth, 
		unsigned int savedMaxHealth, unsigned int savedAttack, unsigned int savedLevel, std::string savedName);

	~Soldier();

private:

};

#endif // SOLDIER_H