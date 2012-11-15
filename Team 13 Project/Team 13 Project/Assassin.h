#ifndef ASSASSIN_H
#define ASSASSIN_H

#include <string>
#include "Commander.h"
#include "Status.h"

// An Assassin is one of the player types
class Assassin : public Commander
{
public:

	Assassin();

	Assassin(int xPos, int yPos, Direction startDir, Animation animationToUse, 
		unsigned int mHealth, unsigned int startAttack, std::string name);

	Assassin(int savedX, int savedY, Direction savedDir, Animation savedAnimation, unsigned int savedCurrentHealth, 
		unsigned int savedMaxHealth, unsigned int savedAttack, unsigned int savedLevel, std::string savedName);

	~Assassin();

private:

};

#endif // ASSASSIN_H