#pragma once

#include "ShotType.h"

class  SingleShot : public ShotType
{
public:
	SingleShot(void);
	~SingleShot(void);

	void doShot(std::list<Bullet*>& playerBullets, sf::Vector2f pos);
	float shotTime();
	float delay;
};

