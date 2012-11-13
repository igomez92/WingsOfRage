#ifndef SOLDIER_H
#define SOLDIER_H

#include "Commander.h"

// A Soldier is one of the player types
class Soldier : public Commander
{
public:
	// Starting Contructor
	Soldier(int initialX, int initialY, int initialHealth, int initialAttack, std::string playerName);
	// Saved Character Constructor
	Soldier(int savedX, int savedY, int savedCurrentHealth, int savedMaxHealth, int savedAttack, int savedLevel, int savedEXP, Status* savedList, std::string savedName);
	// Destructor in case we need to remove any dynamically-allocated pointer
	~Soldier();

	// Add all of the functions a Soldier can do here
	// This includes:
	/*
		Special Attacks
		Additional Range
		Movement Speed
	*/

	// The functions depend on what the designers want us to implement

private:
	// You will need to add members here as we continue programming
};

#endif // SOLDIER_H