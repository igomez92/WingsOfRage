#include "Bullet.h"


Bullet::Bullet(std::string file)
	:VisibleObject(file)
{
}


Bullet::~Bullet(void)
{
}

void Bullet::update(float deltaTime)
{
	position += velocity * deltaTime;
}

sf::Vector2f Bullet::getPosition()
{
	return position;
}