#pragma once

#include "ShotType.h"

class  SingleShot : public ShotType
{
public:
	SingleShot(float delay);
	~SingleShot(void);

	void doShot(std::list<Bullet*>& playerBullets, sf::Vector2f pos, sf::Vector2f dir);
	float shotTime();
	float delay;
};

