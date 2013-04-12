#pragma once

#include "Enemy.h"

class Boss1 : public Enemy
{
	public:
		Boss1(std::string file, sf::Vector2f pos, int health = 500);
		~Boss1(void);

		virtual void update(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, Player& player);
		
		
		void attackPattern1(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, sf::Vector2f player_pos);
		void attackPattern2(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, sf::Vector2f player_pos);
		void attackPattern3(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, sf::Vector2f player_pos);

		float attackswitchtimer;
};