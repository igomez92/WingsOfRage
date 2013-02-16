#pragma once

#include <SFML/System.hpp>
#include "AnimSprite.h"
#include "IScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <list>

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
	Enemy enemy;

	std::list<Bullet*> playerBullets;
	std::list<Bullet*> enemyBullets;

	sf::Clock clock;
	sf::Time lastFrameTime;
};