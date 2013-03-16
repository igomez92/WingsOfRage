#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "Bullet.h"
enum EnemyType {Normal , Reflector, Tank, Melee};

class Enemy
{
	public:
		Enemy(std::string file, sf::Vector2f pos, int health = 100);
		~Enemy(void);

		virtual void update(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, sf::Vector2f player_pos);
		void draw(sf::RenderWindow& window);
		virtual void takeDam(int dam);
		bool isDead();
		int getHealth();
		int collisiondamage();

		sf::Vector2f pos;
		sf::Clock bulletClock;
		sf::FloatRect getSize();

		EnemyType type;
	protected:
		int health;
		int collisiondmg;
		sf::Sprite sprite;
};

