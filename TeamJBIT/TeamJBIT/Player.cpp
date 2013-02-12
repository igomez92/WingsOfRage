#include "Player.h"

Player::Player(std::string file, int x, int y)
	:VisibleObject(file), health(3), xPos(x), yPos(y)
{
	getSprite().setOrigin(getSprite().getLocalBounds().width/2, getSprite().getLocalBounds().height/2);
}


Player::~Player()
{
}


void Player::update()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		yPos += 5;
		setPosition(xPos, yPos);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		yPos -= 5;
		setPosition(xPos, yPos);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		xPos -= 5;
		setPosition(xPos, yPos);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		xPos += 5;
		setPosition(xPos, yPos);
	}

	if(getBounds().top + getBounds().height > 600)
	{
		yPos = 600 - getBounds().height;
		setPosition(xPos, yPos);
	}
	if(getBounds().top < 0)
	{
		yPos = 0.01;
		setPosition(xPos, yPos);
	}
	if(getBounds().left + getBounds().width > 800)
	{
		xPos = 800 - getBounds().width;
		setPosition(xPos, yPos);
	}
	if(getBounds().left < 0)
	{
		xPos = 0.01;
		setPosition(xPos, yPos);
	}
}