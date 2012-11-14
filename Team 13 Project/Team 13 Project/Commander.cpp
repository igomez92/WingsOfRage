#include "Commander.h"


// This is the default Commander constructor
Commander::Commander(int initialX, int initialY, int initialHealth, int initialAttack, std::string startName)
	:Character(initialX, initialY, initialHealth, initialAttack), level(1), experience(0), playerName(startName)
{}

// This is the saved Commander constructor
Commander::Commander(int savedX, int savedY, int savedCurrentHealth, int savedMaxHealth, int savedAttack, int savedLevel,
					 int savedEXP, std::string savedName)
					 // Status* savedStatuses, std::string savedName)
	:Character(savedX, savedY, savedCurrentHealth, savedMaxHealth, savedAttack),
	//savedStatuses)
			  level(savedLevel),
	experience(savedEXP), playerName(savedName)
{}

// This is the destructor of the Commander Object
Commander::~Commander()
{

}