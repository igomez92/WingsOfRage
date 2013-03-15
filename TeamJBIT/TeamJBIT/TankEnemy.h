#pragma once
#include "Enemy.h"

class TankEnemy : public Enemy
{
public:
TankEnemy(std::string file, sf::Vector2f pos, int health = 1000);
	~TankEnemy(void);

	void update(float deltaTime, std::list<Bullet*>& eList, sf::Vector2f player_pos);

};