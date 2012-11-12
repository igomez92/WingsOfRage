//Assassin.cpp
#include "Assassin.h"

// Constructs a starting Character, setting up for starting the game
Assassin::Assassin(int initialX, int initialY, int initialHealth, int initialAttack, std::string startName)
	:Commander(initialX, initialY, initialHealth, initialAttack, startName)
{}

// Constructs a saved Character object, setting up for continuing the game
Assassin::Assassin(int savedX, int savedY, int savedCurrentHealth, int savedMaxHealth, int savedAttack, int savedLevel, int savedEXP, Status* savedList, std::string savedName)
	:Commander(savedX, savedY, savedCurrentHealth, savedMaxHealth, savedAttack, savedLevel, savedEXP, savedList, savedName)
{}

// Can be removed if not needed
Assassin::~Assassin ()
{}