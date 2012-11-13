// Status.cpp
// This is where all of the status types branch from.
// For now, we only have Poison, Sleep, increased/decreased damage, increased/decreased movement, and increased/decreased health
#include <iostream>
#include "Status.h"

Status::Status(int enteredStatus)
	: statusType(enteredStatus)
{

}

void Status::doAction(Character& being)
{

	if(this->statusType == POISON)
	{
		// Lower Character's current health over time
		// Only a potion can heal
	}
	else if(this->statusType == SLEEP)
	{
		// Don't allow the Character to move
		// Only lasts for a set amount of turns
	}
	else if(this->statusType == BLEEDING)
	{
		// Lower Charater's current health over time
		// Fixed after healing
	}
	else if(this->statusType == DAMAGE_INCREASE)
	{
		// Increases the Character's Damage Power
		// Only for a set amount of turns
	}
	else if(this->statusType == DAMAGE_DECREASE)
	{
		// Decreases the Character's Damage Power
		// Only for a set amount of turns
	}
	else if(this->statusType == HEALTH_INCREASE)
	{
		// Increases the Character's Health
		// Only for a set amount of turns
	}
	else if(this->statusType == HEALTH_DECREASE)
	{
		// Decreases the Character's Health
		// Only for a set amount of turns
	}
	else if(this->statusType == MOVEMENT_INCREASE)
	{
		// Increases the Character's amount of movement
		// Only for a set amount of turns
	}
	else if(this->statusType == MOVEMENT_DECREASE)
	{
		// Decreases the Character's amount of movement
		// Only for a set amount of turns
	}
}