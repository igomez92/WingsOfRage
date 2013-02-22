#include "Enemy.h"


Enemy::Enemy(std::string file, sf::Vector2f pos, int health)
	:pos(pos), health(health)
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
	pos.y += 100 * deltaTime;
	sprite.setPosition(pos);
	if(pos.y > 600 + sprite.getLocalBounds().height)
	{
		pos.y -= 600 + sprite.getLocalBounds().height;
		sprite.setPosition(pos);
	}
}

void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Enemy::takeDam(int dam)
{
	health -= dam;
}

bool Enemy::isDead()
{
	if(health <= 0)
		return true;
	
	return false;
}