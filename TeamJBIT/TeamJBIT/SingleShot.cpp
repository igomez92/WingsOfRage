#include "SingleShot.h"


SingleShot::SingleShot(float delay)
	:delay(delay)
{
}


SingleShot::~SingleShot(void)
{
}

void SingleShot::doShot(std::list<Bullet*>& playerBullets, sf::Vector2f pos, sf::Vector2f dir)
{
	playerBullets.push_back(new Bullet("bullet.png", pos, sf::Vector2f(1600*dir.x, 1600*dir.y)));
}

float SingleShot::shotTime()
{
	return delay;
}