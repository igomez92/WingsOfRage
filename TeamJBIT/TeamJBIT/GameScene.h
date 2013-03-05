#pragma once

#include <SFML/System.hpp>
#include "AnimSprite.h"
#include "IScene.h"
#include "Player.h"

#include "Enemy.h"
#include "TankEnemy.h"
#include "Bullet.h"
#include "PowerUp.h"
#include <list>
#include <sstream>

class GameScene : public IScene
{
public:
	GameScene();
	~GameScene();
	
	virtual void update(sf::RenderWindow& window);
	virtual void draw(sf::RenderWindow& window);
	virtual bool handleEvent(sf::Event& event);

private:
	sf::Texture animSpriteTexture;
	AnimSprite testSprite;

	Player player;
	PowerUp testDummy;
	sf::Time shotTimer;
	int enemyDisplacement;

	std::list<Enemy*> enemyList;
	std::list<Bullet*> playerBullets;
	std::list<Bullet*> enemyBullets;

	sf::Clock clock;
	sf::Time lastFrameTime;

	// Score stuff
	std::stringstream scoreStr;
	sf::Text score;
	sf::Font tempestaSevenFont;
	unsigned int scoreNum;

	// Time stuff
	std::stringstream timeStr;
	sf::Text timer;

	void initializeScoreAndTime();
	void updateScoreAndTime();
	void printScoreAndTime(sf::RenderWindow& window);
};