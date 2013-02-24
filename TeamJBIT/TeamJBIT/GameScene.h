#pragma once

#include <SFML/System.hpp>
#include "AnimSprite.h"
#include "IScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <list>
#include <sstream>

class GameScene : public IScene
{
public:
	GameScene();
	~GameScene();
	
	virtual void update();
	virtual void draw(sf::RenderWindow& window);
	virtual bool handleEvent(sf::Event& event);

private:
	sf::Texture animSpriteTexture;
	AnimSprite testSprite;

	Player player;
	sf::Time shotTimer;
	int enemyDisplacement;

	std::list<Enemy*> enemyList;
	std::list<Bullet*> playerBullets;
	std::list<Bullet*> enemyBullets;

	std::stringstream scoreStr;
	sf::Text score;
	sf::Font tempestaSevenFont;
	unsigned int scoreNum;

	sf::Clock clock;
	sf::Time lastFrameTime;

	void initializeScore();
	void updateScore();
	void printScore(sf::RenderWindow& window);
};