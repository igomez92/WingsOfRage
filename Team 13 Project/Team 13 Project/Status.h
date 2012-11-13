#ifndef STATUS_H
#define STATUS_H

#include <string>
#include "Character.h"

// We may not need an enumeration, but it's just to help set up if we need it
enum statusEnum
{
	POISON,
	SLEEP,
	BLEEDING,
	DAMAGE_INCREASE,
	DAMAGE_DECREASE,
	HEALTH_INCREASE,
	HEALTH_DECREASE,
	MOVEMENT_INCREASE,
	MOVEMENT_DECREASE
};

class Status
{
public:
	// Constructs a Status object
	Status(int enteredStatus);

	// Does a status effect on the character
	void doAction(Character& being);

private:
	// The Status should know what it is
	int statusType;
};

#endif // STATUS_H