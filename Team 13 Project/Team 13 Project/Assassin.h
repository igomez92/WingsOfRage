#ifndef ASSASSIN_H
#define ASSASSIN_H

#include <string>
#include "Commander.h"
#include "Status.h"

// An Assassin is one of the player types
class Assassin : public Commander
{
public:
	// Starting constructor
	Assassin(int initialX, int initialY, int initialHealth, int initialAttack, std::string playerName);
	// Saved Character constructor
	Assassin(int savedX, int savedY, int savedCurrentHealth, int savedMaxHealth, int savedAttack, int savedLevel, int savedEXP, Status* savedList, std::string savedName);
	// Destructor in case we need any dynamically-allocated pointer removed
	~Assassin();
private:
	// You will need to add members here
};

#endif // ASSASSIN_H