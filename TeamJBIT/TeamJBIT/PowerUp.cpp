#include "PowerUp.h"
#include "TextureManager.h"

PowerUp::PowerUp(sf::Vector2f pos)
	:pos(pos)
{
	float x = rand() % 10;
	sf::Texture* image;
	if(x < 2)
	{
		image = _getTexture("media/power.png");
		upgradeType = WEAPON_UPGRADE;
	}
	else if(x < 6)
	{
		image = _getTexture("media/power.png");
		upgradeType = HEALTH_UPGRADE;
	}
	else
	{
		image = _getTexture("media/power.png");
		upgradeType = ENERGY_UPGRADE;
	}

	sprite.setTexture(*image);
	sprite.setPosition(pos);
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);


}

PowerUp::~PowerUp()
{
	
}

void PowerUp::setTime(float startTime)
{
	PowerUp::startTime = startTime;
}

void PowerUp::setPosition(sf::Vector2f position)
{
	pos = position;
	sprite.setPosition(pos);
}

void PowerUp::update(sf::Clock clock)
{
	if(clock.getElapsedTime().asSeconds() > startTime + 50)
		PowerUp::~PowerUp();
}

void PowerUp::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

int PowerUp::getUpgradeType()
{
	return upgradeType;
}
