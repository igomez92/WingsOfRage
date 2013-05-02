#pragma once

#include "BeamSword.h"

class ShotSword : public BeamSword
{
public:
	ShotSword(std::string file,float delay, sf::Vector2f dir, sf::Vector2f pos, float damage = 30.f, float swingSpeed = 5000.f);
	~ShotSword(void);

	void update(float deltaTime, sf::Vector2f pos, std::list<Bullet*>& playerBullets);

	bool shotDone;
};

