#pragma once

#include "Enemy.h"

class CircleEnemy : public Enemy
{
	public:
		CircleEnemy(std::string file, sf::Vector2f pos, int health = 100);
		void update(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, Player& player);

	private:
		sf::Vector2f localTargetPos;
		float currentTargetAngle;
};
