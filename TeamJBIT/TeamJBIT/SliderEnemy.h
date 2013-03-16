#pragma once

#include "Enemy.h"

class SliderEnemy : public Enemy
{
	public:
		SliderEnemy(std::string file, sf::Vector2f pos, int health = 10);
		~SliderEnemy(void);

		void update(float deltaTime, std::list<Bullet*>& eList, sf::Vector2f player_pos);
	
		bool goingdown;
		float dir;

	private:
		float initial_pos;
};