#pragma once

#include "Enemy.h"

class SpiralEnemy : public Enemy
{
	public: 
		float coolTime;
		int currentTime;
		bool fireSpiral;
		int bulletSpeed;
		SpiralEnemy(std::string file, sf::Vector2f pos, int health, float coolTime);
		~SpiralEnemy(void);
		void update(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, Player& player);

};