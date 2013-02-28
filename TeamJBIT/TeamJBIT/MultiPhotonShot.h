#pragma once

#include "ShotType.h"

class MultiPhotonShot : public ShotType
{
public:
	MultiPhotonShot(void);
	~MultiPhotonShot(void);

	void doShot(std::list<Bullet*>& playerBullets, sf::Vector2f pos);
	float shotTime();
	float delay;
};

