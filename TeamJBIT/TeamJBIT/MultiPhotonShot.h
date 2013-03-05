#pragma once

#include "ShotType.h"

class MultiPhotonShot : public ShotType
{
public:
	MultiPhotonShot(void);
	~MultiPhotonShot(void);

	void doShot(std::list<Bullet*>& playerBullets, sf::Vector2f pos, sf::Vector2f dir);
	float shotTime();
	float delay;
};

