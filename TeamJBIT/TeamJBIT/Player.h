#pragma once

#include <SFML/Graphics.hpp>
#include "AnimSprite.h"
class Player
{
public:
	Player(std::string file, sf::Vector2f pos);
	~Player();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	sf::Vector2f pos;

private:
	unsigned int health;
	unsigned int level;

	AnimSprite sprite;
	sf::Texture image;
};