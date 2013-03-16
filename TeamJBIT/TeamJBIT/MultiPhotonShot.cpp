#include "MultiPhotonShot.h"
#include "Utility.h"

MultiPhotonShot::MultiPhotonShot(void)
	:delay(0.15f)
{

}


MultiPhotonShot::~MultiPhotonShot(void)
{

}

void MultiPhotonShot::doShot(std::list<Bullet*>& playerBullets, sf::Vector2f pos, sf::Vector2f dir)
{
	// Left bullets
	playerBullets.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(-(sin(37.5*M_PI/180)*400), cos(37.5*M_PI/180)*-400 ), 10));
	playerBullets.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(-(sin(30*M_PI/180)*400), cos(30*M_PI/180)*-400),10));
	playerBullets.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(-(sin(22.5*M_PI/180)*400), cos(22.5*M_PI/180)*-400),10));
	playerBullets.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(-(sin(15*M_PI/180)*400), cos(15*M_PI/180)*-400),10));
	playerBullets.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(-(sin(7.5*M_PI/180)*400), cos(7.5*M_PI/180)*-400),10));
	// Center bullet does double damage	
	playerBullets.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(0, -400), 20));
	// Right bullets					
	playerBullets.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(sin(37.5*M_PI/180)*400, cos(37.5*M_PI/180)*-400),10));
	playerBullets.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(sin(30*M_PI/180)*400, cos(30*M_PI/180)*-400),10));
	playerBullets.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(sin(22.5*M_PI/180)*400, cos(22.5*M_PI/180)*-400),10));
	playerBullets.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(sin(15*M_PI/180)*400, cos(15*M_PI/180)*-400),10));
	playerBullets.push_back(new Bullet("media/bullet.png", pos, sf::Vector2f(sin(7.5*M_PI/180)*400, cos(7.5*M_PI/180)*-400),10));
}

float MultiPhotonShot::shotTime()
{
	return delay;
}
