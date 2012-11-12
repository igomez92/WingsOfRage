#ifndef COMMANDER_H
#define COMMANDER_H

#include "Character.h"
#include "Status.h"
#include <string>

// A commander is a type of Character.  The player will choose a commander to play as.
class Commander : public Character
{
public:
	// Constructs a starting Commander character
	Commander(int initialX, int initialY, int initialHealth, int initialAttack, std::string startName);
	// Constructs a saved Commander character
	Commander(int savedX, int savedY, int savedCurrentHealth, int savedMaxHealth, int savedAttack, int savedLevel, int savedEXP, Status* savedStatuses, std::string savedName);
	// In case we need to remove any dynamically-allocated pointer
	~Commander();
private:
	// You may need to add more members here
	int level;
	int experience;
	std::string playerName;
};

#endif // COMMANDER_H