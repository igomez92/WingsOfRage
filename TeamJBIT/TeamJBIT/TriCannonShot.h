#pragma once

#include "ShotType.h"

class TriCannonShot : public ShotType
{
public:
	TriCannonShot();
	~TriCannonShot();

	void doShot(std::list<Bullet*>& playerBullets, sf::Vector2f pos, sf::Vector2f dir);
	float shotTime();
	float delay;
};

