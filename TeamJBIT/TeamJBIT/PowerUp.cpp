#include "PowerUp.h"
#include "TextureManager.h"
#include "Utility.h"

PowerUp::PowerUp(sf::Vector2f pos, int startTime)
	:pos(pos), startTime(startTime)
{
	deltaPos.x = 3;
	deltaPos.y = 3;
	float x = rand() % 10;
	sf::Texture* image;
	if(x < 3)
	{
		image = _getTexture("media/power.png");
		upgradeType = WEAPON_UPGRADE;
	}
	else if(x < 6)
	{
		image = _getTexture("media/health.png");
		upgradeType = HEALTH_UPGRADE;
	}
	else if(x < 9)
	{
		image = _getTexture("media/energy.png");
		upgradeType = ENERGY_UPGRADE;
	}
	else
	{
		image = _getTexture("media/bombTemp.png");
		upgradeType = BOMB_UPGRADE;
	}
	currentTime = startTime;
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

void PowerUp::update()
{
	currentTime++;
	
	if(pos.x >= SCREEN_WIDTH || pos.x <= 0 )
	{
		deltaPos.x = deltaPos.x * -1;
	}
	if(pos.y >= SCREEN_HEIGHT || pos.y <= 0 )
	{
		deltaPos.y = deltaPos.y* -1;
	}
	pos += deltaPos;
	sprite.setPosition(pos);
}

void PowerUp::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

int PowerUp::getUpgradeType()
{
	return upgradeType;
}
