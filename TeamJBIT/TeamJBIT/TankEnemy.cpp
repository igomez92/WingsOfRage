#include "TankEnemy.h"
#include "Utility.h"

TankEnemy::TankEnemy(std::string file, sf::Vector2f pos, int health)
	:Enemy(file,pos,health)
{
	collisiondmg = 100;
	type = Tank;
}
void TankEnemy::update(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, sf::Vector2f player_pos)
{
	sf::Vector2f enemyMove = normalize(pos - player_pos);

	pos -= enemyMove * (150 * deltaTime);
	sprite.setPosition(pos);
	if(pos.y > 600 + sprite.getLocalBounds().height)
	{
		pos.y -= 600 + sprite.getLocalBounds().height;
		sprite.setPosition(pos);
	}

}
