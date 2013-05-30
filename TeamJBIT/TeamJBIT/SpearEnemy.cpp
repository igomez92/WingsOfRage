#include <math.h>
#include "SpearEnemy.h"
#include "Utility.h"

#define SPEAR_MOVETIME 1.5
//
//
//SpearEnemy::SpearEnemy(std::string file, sf::Vector2f pos, int health)
//	:Enemy(file, pos, health), meleeActive (false), coolTime(20), currentTime(100), attackTime (50),
//	float attackTime;	
//	float dashSpeed;	
//	enemMelee* melee;
//{
//}
//
//
//SpearEnemy::~SpearEnemy(void)
//{
//}
//
//
//void SpearEnemy::update(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, Player& player)
//{
//	// attack the player when ready
//	if (this->readyToAttack())
//	{
//		sf::Vector2f enemyMove = normalize(pos - player.pos);
//		pos -= enemyMove * (100 * deltaTime);
//		sprite.setPosition(pos);
//		sprite.setRotation((-atan2f(-enemyMove.x, -enemyMove.y) * (180 / 3.1415926f)) + 180.f);
//	}
//	// not ready to attack the player, so pause (keeps same position)
//	else
//	{
//
//	}
//
//}
//
//
//void SpearEnemy::draw(sf::RenderWindow& window)
//{
//	if(meleeActive)
//	{
//		melee->draw(window);
//	}
//
//	window.draw(sprite);
//}
//
//
//	
//
//bool SpearEnemy::readyToAttack()
//{
//	return currentTime >= attackTime;
//}
//



	//SpearEnemy(std::string file, sf::Vector2f pos, int health);
	//~SpearEnemy(void);

	//virtual void update(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, Player& player);
	//virtual void draw(sf::RenderWindow& window);
	//virtual void takeDam(int dam);

	//float coolTime;
	//int dashSpeed;
	//
	//// I'm guessing this is the next position?
	//Sequence spearSequenceX;
	//Sequence spearSequenceY;
