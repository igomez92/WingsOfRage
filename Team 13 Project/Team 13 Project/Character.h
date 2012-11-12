#include "Status.h"

// A Character is an entity in the game.  All Characters(Player, enemies, NPC, etc.) branch from this class
class Character
{
public:
	// Constructs a default Character
	Character(int initialX, int initialY, int initialHealth, int initialAttack);
	// Constructs a saved Characer(Mainly for the player)
	Character(int savedX, int savedY, int savedCurrentHealth, int savedMaxHealth, int savedAttack, Status* savedList);
	// In case we need to destroy any dynamically-allocated pointer
	~Character();

private:
	// We may need to add additional members here
	int xPosition;
	int yPosition;
	int currentHealth;
	int maxHealth;
	int attack;
	// WE CAN CHANGE THE LISTOF STATUS TO NOT BE AN ARRAY
	Status* listOfStatus;
};

