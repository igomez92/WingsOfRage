#pragma once

#include "IScene.h"
#include "Player.h"
#include "Enemy.h"

class GameScene : public IScene
{
public:
	GameScene();
	~GameScene();
	
	virtual void update();
	virtual void draw(sf::RenderWindow& window);
	virtual bool handleEvent(sf::Event& event);

private:
	Player player;
	Enemy enemy;
};