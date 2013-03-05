#pragma once

#include <list>
#include "Bullet.h"

#define PI 3.14159265359

class ShotType
{
public:
	virtual void doShot(std::list<Bullet*>& playerBullets, sf::Vector2f pos, sf::Vector2f dir) = 0;
	virtual float shotTime() = 0;
};

