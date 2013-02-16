#include "Enemy.h"


Enemy::Enemy(std::string file, sf::Vector2f pos)
	:continueDraw(true), pos(pos)
{
	image.loadFromFile(file);
	sprite.setTexture(image);
	sprite.setPosition(pos);
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
}


Enemy::~Enemy(void)
{
}

void Enemy::update(float deltaTime)
{
	if(continueDraw == false)
	{
		sprite.setPosition(-100, -100);
	}
	else
	{
		pos.y += 300 * deltaTime;
		sprite.setPosition(pos);
		if(pos.y > 600 + sprite.getLocalBounds().height)
		{
			pos.y -= 600 + sprite.getLocalBounds().height;
			sprite.setPosition(pos);
		}
	}
}

void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}