#include "GameScene.h"

GameScene::GameScene() : player("ball.png", sf::Vector2f(400, 300)) {

	//TEST STUFF
	animSpriteTexture.loadFromFile("yeah.jpg");
	animSpriteTexture.setSmooth(true);
	testSprite.setTexture(animSpriteTexture);
	testSprite.addAnim("yeah", 0, 0, 95, 10, 30, true);
	testSprite.setFrameSize(200, 217);
	testSprite.playAnim("yeah");
	testSprite.setOrigin(100, 108);
	testSprite.setPosition(400, 300);
	testSprite.setScale(800.f/200, 600.f/217);

	enemyList.push_back(new Enemy("ball.png", sf::Vector2f(400, 100)));
}

GameScene::~GameScene() {

}
	
void GameScene::update() {
	float deltaTime = (clock.getElapsedTime() - lastFrameTime).asSeconds();
	lastFrameTime = clock.getElapsedTime();


	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if((clock.getElapsedTime() - shotTimer).asSeconds() > .1){
		playerBullets.push_back(new Bullet("ball.png", player.pos, sf::Vector2f(0,-400)));
		shotTimer= clock.getElapsedTime();
		}
	}


	//update bullets
	for (auto it = playerBullets.begin(); it != playerBullets.end();) {
		(**it).update(deltaTime);

		//offscreen check
		if ((**it).getPosition().y < -100) {
			auto itToErase = it;
			it++;
			delete (*itToErase);
			playerBullets.erase(itToErase);
			continue;
		}

		bool removeBullet = false;
		for (auto enemyIt = enemyList.begin(); enemyIt != enemyList.end(); enemyIt++)
		{
			int thresholdX = abs((**enemyIt).pos.x - (**it).pos.x);
			int thresholdY = abs((**enemyIt).pos.y - (**it).pos.y);
			if(thresholdX < 22 && thresholdY < 22)
			{
				(**enemyIt).takeDam((**it).dam);
				removeBullet = true;
				break;
			}
		}

		if (removeBullet)
		{
			auto itToErase = it;
			it++;
			delete (*itToErase);
			playerBullets.erase(itToErase);
			continue;
		}


		it++;
	}

	for (auto it = enemyList.begin(); it != enemyList.end();) 
	{
		if((**it).isDead())
		{
			auto itToErase = it;
			it++;
			delete (*itToErase);
			enemyList.erase(itToErase);
			continue;
		}

		(**it).update(deltaTime);
		
		it++;
	}

	player.update(deltaTime);
	testSprite.update(deltaTime);
}

void GameScene::draw(sf::RenderWindow& window) {
	window.draw(testSprite);

	//draw bullets
	for (auto it = playerBullets.begin(); it != playerBullets.end(); it++) {
		(**it).draw(window);
	}	
	for (auto it = enemyList.begin(); it != enemyList.end(); it++) 
	{
		(**it).draw(window);
	}
	player.draw(window);	
}

bool GameScene::handleEvent(sf::Event& event) {
	return false;
}