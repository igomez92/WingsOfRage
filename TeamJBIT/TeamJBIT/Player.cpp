#include "Player.h"

Player::Player(std::string file, sf::Vector2f pos)
	:health(3), pos(pos)
{
	image.loadFromFile(file);
	sprite.setTexture(image);
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
}


Player::~Player()
{
}


void Player::update(float deltaTime)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		pos.y += 300 * deltaTime;
		sprite.setPosition(pos);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		pos.y -= 300 * deltaTime;
		sprite.setPosition(pos);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		pos.x -= 300 * deltaTime;
		sprite.setPosition(pos);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		pos.x += 300 * deltaTime;
		sprite.setPosition(pos);
	}

	if(sprite.getGlobalBounds().top + sprite.getGlobalBounds().height > 600)
	{
		pos.y = 600 - sprite.getGlobalBounds().height;
		sprite.setPosition(pos);
	}
	if(sprite.getGlobalBounds().top < 0)
	{
		pos.y = sprite.getGlobalBounds().height / 2;
		sprite.setPosition(pos);
	}
	if(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width > 800)
	{
		pos.x = 800 - sprite.getGlobalBounds().width;
		sprite.setPosition(pos);
	}
	if(sprite.getGlobalBounds().left < 0)
	{
		pos.x = sprite.getGlobalBounds().width / 2;
		sprite.setPosition(pos);
	}
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}