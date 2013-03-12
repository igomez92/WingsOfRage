#pragma once

#include "MeleeType.h"

class SwordSlash : public MeleeType
{
public:
	SwordSlash(float delay);
	~SwordSlash();

	void doMeleeAttack(sf::Vector2f pos);
	float meleeTime();
	float delay;

};