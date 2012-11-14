#include "Soldier.h"

// Constructs a default Soldier object, one of the player types
Soldier::Soldier(int initialX, int initialY, int initialHealth, int initialAttack, std::string startName)
	:Commander(initialX, initialY, initialHealth, initialAttack, startName)
{}

// Constructs a saved Soldier object
Soldier::Soldier(int savedX, int savedY, int savedCurrentHealth, int savedMaxHealth, int savedAttack, int savedLevel, int savedEXP, Status* savedList, std::string savedName)
	:Commander(savedX, savedY, savedCurrentHealth, savedMaxHealth, savedAttack, savedLevel, savedEXP,
	//savedList,
	savedName)
{}

// Can be removed if not needed
Soldier::~Soldier()
{}