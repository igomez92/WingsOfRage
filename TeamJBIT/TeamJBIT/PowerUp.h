#pragma once

#include <SFML/Graphics.hpp>
#include "AnimSprite.h"

class PowerUp
{
	public:
		PowerUp(std::string file, sf::Vector2f pos);
		~PowerUp();

		void update(sf::Clock clock);
		void draw(sf::RenderWindow& window);
		void setTime(float startTime);
		void setPosition(sf::Vector2f pos);
		sf::Vector2f pos;
		float startTime;
		bool isHP;
		bool isEnergy;

	private:
		AnimSprite sprite;
};