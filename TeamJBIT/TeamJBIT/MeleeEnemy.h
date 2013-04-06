#pragma once
#include "Enemy.h"
#include "enemMelee.h"
#include "Utility.h"

class MeleeEnemy : public Enemy
{
	public:
		MeleeEnemy(std::string file, sf::Vector2f pos, int health = 1, float coolTime = 5);
		~MeleeEnemy(void);

		void update(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, Player& player);
		void draw(sf::RenderWindow& window);
		void doMelee(sf::Vector2f player_pos);

	private:
		bool meleeActive;
		bool allowMelee;
		bool didDam;
		float coolTime;
		float currTime;
		enemMelee* melee;
};
