#include "MeleeEnemy.h"
#include "Utility.h"

MeleeEnemy::MeleeEnemy(std::string file, sf::Vector2f pos, int health, float coolTime)
	:Enemy(file,pos,health), allowMelee(true), coolTime(coolTime), currTime(0), meleeActive(false), didDam(false)
{
	collisiondmg = 10;
	type = Melee;
}

MeleeEnemy::~MeleeEnemy(void)
{
	if(meleeActive)
		delete melee;
}

void MeleeEnemy::update(float deltaTime, std::list<Bullet*>& eList, std::list<Bullet*>& pList, Player& player)
{
	// If the enemy attacked the player
	if(allowMelee == false)
	{
		sf::Vector2f enemyMove = normalize(pos - player.pos);
		enemyMove.x = -enemyMove.x;
		enemyMove.y = -enemyMove.y;
		pos -= enemyMove * (100 * deltaTime);
		sprite.setPosition(pos);
		sprite.setRotation((-atan2f(-enemyMove.x, -enemyMove.y) * (180 / 3.1415926f)) + 180.f);

		// Update the timer
		currTime += deltaTime;
	}
	// Move the enemy towards the player
	else
	{
		sf::Vector2f enemyMove = normalize(pos - player.pos);
		pos -= enemyMove * (100 * deltaTime);
		sprite.setPosition(pos);
		sprite.setRotation((-atan2f(-enemyMove.x, -enemyMove.y) * (180 / 3.1415926f)) + 180.f);
	}

	// If the player is within range
	int thresholdX = abs(pos.x - player.pos.x);
	int thresholdY = abs(pos.y - player.pos.y);
	if(thresholdX <= 2*sprite.getLocalBounds().width && thresholdY <= 2*sprite.getLocalBounds().height)
	{
		if(allowMelee)
		{
			// Do melee
			doMelee(player.pos);
			allowMelee = false;
			meleeActive = true;
		}
	}

	// If the melee cooldown is less than the current time
	if(currTime >= coolTime)
	{
		// Move allow enemy to attack again.
		currTime = 0;
		allowMelee = true;
	}
	// If the melee is active
	if(meleeActive)
	{
		// If we want to end the attack
		if(melee->endSwing)
		{
			delete melee;
			meleeActive = false;
			didDam = false;
		}
		else
		{
			melee->update(deltaTime, pos);

			if(melee->collidesWith(player)&& didDam == false)
			{
				melee->doDamage(player);
				didDam = true;
			}
		}
	}
}

void MeleeEnemy::draw(sf::RenderWindow& window)
{
	if(meleeActive)
	{
		melee->draw(window);
	}

	window.draw(sprite);
}

void MeleeEnemy::doMelee(sf::Vector2f player_pos)
{
	sf::Vector2f dir = player_pos-pos;
	dir = normalize(dir);

	melee = new enemMelee("media/sword.png", 0, dir, pos, 30.f, 1000.f);
	meleeActive = true;
}