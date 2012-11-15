#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include "Character.h"
#include "Status.h"

enum EnemyType
{
	HUMAN,
	ZOMBIE,
	MACHINE,
	MUTATION
};

// An enemy is a type of Character.  All Enemy types branch from this class
class Enemy : public Character
{
public:
	Enemy();

	Enemy(int xPos, int yPos, Direction startDir, Animation animationToUse, 
		unsigned int mHealth, unsigned int startAttack, std::string name);

	Enemy(int savedX, int savedY, Direction savedDir, Animation savedAnimation, unsigned int savedCurrentHealth, 
		unsigned int savedMaxHealth, unsigned int savedAttack, unsigned int savedLevel, std::string savedName);

	~Enemy();

private:
	std::string enemyName;
};

#endif // ENEMY_H