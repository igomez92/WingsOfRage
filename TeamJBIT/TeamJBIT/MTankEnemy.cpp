#include "MTankEnemy.h"
#include "Utility.h"

MTankEnemy::MTankEnemy(std::string file, sf::Vector2f pos, int health)
	:Enemy(file,pos,health)
{
	collisiondmg = 100;
	type = Reflector;
}
void MTankEnemy::update(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, Player& player)
{
	sf::Vector2f enemyMove = normalize(pos - player.pos);

	pos -= enemyMove * (100 * deltaTime);
	
	sprite.setPosition(pos);
}

void MTankEnemy::takeDam(int damage)
{
	health = 0;
}
