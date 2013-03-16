#pragma once

#include "Enemy.h"

class MTankEnemy : public Enemy
{
	public:
		MTankEnemy(std::string file, sf::Vector2f pos, int health = 1);
		~MTankEnemy(void);

		void update(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, sf::Vector2f player_pos);
		void takeDam(int damage);
};