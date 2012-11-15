#include "Enemy.h"

Enemy::Enemy()
		:Character()
{
}

Enemy::Enemy(int xPos, int yPos, Direction startDir, Animation animationToUse, 
		unsigned int mHealth, unsigned int startAttack, std::string name)
		:Character(xPos, yPos, startDir, animationToUse, mHealth, startAttack), enemyName(name)
{}

Enemy::Enemy(int savedX, int savedY, Direction savedDir, Animation savedAnimation, unsigned int savedCurrentHealth, 
		unsigned int savedMaxHealth, unsigned int savedAttack, unsigned int savedLevel, std::string savedName)
		:Character(savedX, savedY, savedDir, savedAnimation, savedCurrentHealth, savedMaxHealth, savedAttack, savedLevel), enemyName(savedName)
{}

Enemy::~Enemy()
{}