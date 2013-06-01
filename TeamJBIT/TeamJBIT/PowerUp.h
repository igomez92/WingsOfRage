#pragma once

#include <SFML/Graphics.hpp>
#include "AnimSprite.h"

enum powerUpType {WEAPON_UPGRADE, HEALTH_UPGRADE, ENERGY_UPGRADE, BOMB_UPGRADE};

class PowerUp
{
	public:
		PowerUp(std::string file, sf::Vector2f pos);
		PowerUp(sf::Vector2f pos, int startTime);
		~PowerUp();

		void update();
		void draw(sf::RenderWindow& window);
		void setTime(float startTime);
		void setPosition(sf::Vector2f pos);
		sf::Vector2f pos;
		int startTime;
		int currentTime;
		bool isHP;
		bool isEnergy;
		int upgradeType;
		int getUpgradeType();

	private:
		AnimSprite sprite;
};