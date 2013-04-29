#include "TankEnemy.h"
#include "Utility.h"

TankEnemy::TankEnemy(std::string file, sf::Vector2f pos, int health)
	:Enemy(file,pos,health)
{
	collisiondmg = 100;
	type = Tank;
}
void TankEnemy::update(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, Player& player)
{
	sf::Vector2f enemyMove = normalize(pos - player.pos);

	pos -= enemyMove * (150 * deltaTime);
	sprite.setPosition(pos);
	if(pos.y > 600 + sprite.getLocalBounds().height)
	{
		pos.y -= 600 + sprite.getLocalBounds().height;
		sprite.setPosition(pos);
	}

	sprite.setRotation((-atan2f(-enemyMove.x, -enemyMove.y) * (180 / 3.1415926f)) + 180.f);
}
