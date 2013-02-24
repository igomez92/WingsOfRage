#include "SingleShot.h"


SingleShot::SingleShot(void)
	:delay(0.1f)
{
}


SingleShot::~SingleShot(void)
{
}

void SingleShot::doShot(std::list<Bullet*>& playerBullets, sf::Vector2f pos)
{
	playerBullets.push_back(new Bullet("ball.png", pos, sf::Vector2f(0, -400)));
}

float SingleShot::shotTime()
{
	return delay;
}