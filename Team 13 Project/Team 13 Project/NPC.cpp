#include "NPC.h"

// Constructs a default NPC object
NPC::NPC(int initialX, int initialY, int initialHealth, int initialAttack, bool isAttackable)
	:Character(initialX, initialY, initialHealth, initialAttack), attackable(isAttackable)
{
}

// Destroys any dynamically-allocated pointers.  Can be removed if unnecessary
NPC::~NPC()
{
}
