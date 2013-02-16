#include "Bullet.h"


Bullet::Bullet(std::string file, sf::Vector2f pos, sf::Vector2f vel)
	:pos(pos), vel(vel)
{
	image.loadFromFile(file);
	sprite.setTexture(image);

	sprite.setPosition(pos);
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);

	sprite.setColor(sf::Color(255, 200, 0, 255));
}


Bullet::~Bullet(void)
{
}

void Bullet::update(float deltaTime)
{
	pos += vel * deltaTime;
	sprite.setPosition(pos);
}

sf::Vector2f Bullet::getPosition()
{
	return pos;
}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}