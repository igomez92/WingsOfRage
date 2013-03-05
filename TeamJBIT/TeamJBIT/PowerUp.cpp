#include "PowerUp.h"

PowerUp::PowerUp(std::string file, sf::Vector2f pos)
	:pos(pos)
{
	image.loadFromFile(file);
	sprite.setTexture(image);
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

void PowerUp::update(sf::Clock clock)
{
	if(clock.getElapsedTime().asSeconds() > startTime + 50)
		PowerUp::~PowerUp();
}

void PowerUp::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}