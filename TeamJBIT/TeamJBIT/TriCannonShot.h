#pragma once

#include "ShotType.h"

class TriCannonShot : public ShotType
{
public:
	TriCannonShot();
	~TriCannonShot();

	void doShot(std::list<Bullet*>& playerBullets, sf::Vector2f pos);
	float shotTime();
	float delay;
};

