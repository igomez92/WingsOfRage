#include "Character.h"

// Creates a default Character for the start of the game
Character::Character(int initialX, int initialY, int initialHealth, int initialAttack)
	:xPosition(initialX), yPosition(initialY), currentHealth(initialHealth), 
	maxHealth(initialHealth), attack(initialAttack), listOfStatus(new Status[5])
{

}

// Creates a saved Character from a saved file
Character::Character(int savedX, int savedY, int savedCurrentHealth, int savedMaxHealth, int savedAttack, Status* savedList)
	:xPosition(savedX), yPosition(savedY), currentHealth(savedCurrentHealth), maxHealth(savedMaxHealth),
	attack(savedAttack), listOfStatus(new Status[5])
{
	// Copies all of the statuses affecting the player
	for(int current = 0; current < 5; current++)
	{
		listOfStatus[current] = savedList[current];
	}

	// Deletes the saved list of statuses so we don't forget to delete it later
	delete[] savedList;
}

// Destroys any dynamically-allocated pointers in the Character class
Character::~Character()
{
	delete[] listOfStatus;
}