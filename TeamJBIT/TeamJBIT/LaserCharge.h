#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

class Enemy;

class LaserCharge
{
	public:
		LaserCharge(sf::Vector2f pos, sf::Vector2f dir, float timeLim = 0.15, int dam = 10000);
		~LaserCharge(void);

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

