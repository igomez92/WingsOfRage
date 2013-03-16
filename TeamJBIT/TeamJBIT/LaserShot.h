#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Enemy.h"

class LaserShot
{
	public:
		LaserShot(sf::Vector2f pos, sf::Vector2f dir, float timeLim = 0.15, int dam = 1000);
		~LaserShot(void);

		void update(float deltaTime);
		void draw(sf::RenderWindow& window);

		float totalTime;
		float accumTime;
		int dam;
		bool continueDraw;

		sf::Vector2f pos;
		sf::Vector2f dir;

		bool collidesWith(Enemy& enemy);

	private:
		sf::Sprite sprite;
};

