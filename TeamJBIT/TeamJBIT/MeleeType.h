#pragma once

#include "ShotType.h"
class MeleeType 
{
public:
	virtual void doMeleeAttack(sf::Vector2f pos) = 0;
	virtual float meleeTime() = 0;

};
