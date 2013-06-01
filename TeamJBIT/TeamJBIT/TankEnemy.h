#pragma once

#include "Enemy.h"

class TankEnemy : public Enemy
{
	public:
		TankEnemy(std::string file, sf::Vector2f pos, int health = 100);
		~TankEnemy(void);

		void update(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, Player& player);
		
};