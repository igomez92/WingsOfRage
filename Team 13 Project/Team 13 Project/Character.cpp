#include "Character.h"

Character::Character(int initialX, int initialY, int initialHealth, int initialAttack)
	:xPosition(initialX), yPosition(initialY), currentHealth(initialHealth), 
	maxHealth(initialHealth), level(1), experience(0), attack(initialAttack)
{

}

Character::Character(int savedX, int savedY, int savedCurrentHealth, int savedMaxHealth, int savedLevel, int savedExperience, int savedAttack, std::vector<Status> savedList)
	:xPosition(savedX), yPosition(savedY), currentHealth(savedCurrentHealth), maxHealth(savedMaxHealth), 
	level(savedLevel), experience(savedExperience), attack(savedAttack), listOfStatus()
{
	for(int current = 0; current < savedList.size(); current++)
	{
	
	}
}

Character::~Character()
{

}