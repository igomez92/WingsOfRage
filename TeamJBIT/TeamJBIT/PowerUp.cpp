#include "PowerUp.h"
#include "TextureManager.h"

PowerUp::PowerUp(std::string file, sf::Vector2f pos)
	:pos(pos)
{
	sf::Texture* image = TextureManager::getInstance().getTexture(file);
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

void PowerUp::setPosition(sf::Vector2f pos)
{
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
