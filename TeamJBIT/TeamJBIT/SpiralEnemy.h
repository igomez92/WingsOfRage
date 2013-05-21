#pragma once

#include "Enemy.h"

class SpiralEnemy : public Enemy
{
	public: 
		float coolTime;
		int currentTime;
		bool fireSpiral;
		int bulletSpeed;
		SpiralEnemy(std::string file, sf::Vector2f pos, int health = 250, float coolTime = 1.5);
		~SpiralEnemy(void);
		void update(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, Player& player);

};