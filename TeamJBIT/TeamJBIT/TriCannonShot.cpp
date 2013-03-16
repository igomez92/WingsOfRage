#include "TriCannonShot.h"
#include "Utility.h"

TriCannonShot::TriCannonShot()
	:delay(0.25f)
{

}

TriCannonShot::~TriCannonShot()
{

}

void TriCannonShot::doShot(std::list<Bullet*>& playerBullets, sf::Vector2f pos, sf::Vector2f dir)
{
	playerBullets.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(-(sin(30*M_PI/180)*400) , -cos(30*M_PI/180)*400)));
	playerBullets.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(0  , -400)));
	playerBullets.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(sin(30*M_PI/180)*400 , -cos(30*M_PI/180)*400)));
}

float TriCannonShot::shotTime()
{
	return delay;
}