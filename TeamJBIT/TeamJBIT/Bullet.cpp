#include "Bullet.h"
#include "TextureManager.h"


Bullet::Bullet(std::string file, sf::Vector2f pos, sf::Vector2f vel, int dam, sf::Color bulletColor)
	:pos(pos), vel(vel), dam(dam)
{
	sf::Texture* image = TextureManager::getInstance().getTexture(file);
	image->setSmooth(true);
	sprite.setTexture(*image);
	sprite.setColor(bulletColor);

	sprite.setPosition(pos);
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
	sprite.setRotation((-atan2f(vel.x, vel.y) * (180 / 3.1415926f)) + 180.f);
	sprite.setScale(2,2);
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
