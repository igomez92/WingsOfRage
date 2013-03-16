#include "GameScene.h"
#include "SceneManager.h"
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

GameScene::GameScene() : player( sf::Vector2f(400, 300)), scoreNum(0) , testDummy("media/ball.png", sf::Vector2f(500,500)), backgroundOffset(0)
{
	// Initialize score info
	initializeScoreAndTime();
	
	enemyDisplacement = 0;
	enemyList.push_back(new TankEnemy("media/ball.png", sf::Vector2f(500,100)));
	enemyList.push_back(new Enemy("media/ball.png", sf::Vector2f(500, 100)));
	
	enemyList.push_back(new SliderEnemy("media/ball.png", sf::Vector2f(0,100)));
	enemyList.push_back(new SliderEnemy("media/ball.png", sf::Vector2f(300,100)));
	enemyList.push_back(new SliderEnemy("media/ball.png", sf::Vector2f(400,100)));
	enemyList.push_back(new SliderEnemy("media/ball.png", sf::Vector2f(500,100)));
	enemyList.push_back(new SliderEnemy("media/ball.png", sf::Vector2f(600,100)));
	enemyList.push_back(new SliderEnemy("media/ball.png", sf::Vector2f(100,100)));
	enemyList.push_back(new SliderEnemy("media/ball.png", sf::Vector2f(200,100)));
	enemyList.push_back(new SliderEnemy("media/ball.png", sf::Vector2f(700,100)));
	enemyList.push_back(new SliderEnemy("media/ball.png", sf::Vector2f(800,100)));
	enemyList.push_back(new SliderEnemy("media/ball.png", sf::Vector2f(399,100)));


	sf::Texture* bgImage = TextureManager::getInstance().getTexture("media/backgrounds/stars.png");
	bgImage->setRepeated(true);
	backgroundSprite.setTexture(*bgImage);
	backgroundSprite.setTextureRect(sf::IntRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT * 2));
	backgroundSprite.setOrigin(0, SCREEN_HEIGHT);
}

GameScene::~GameScene() 
{
	for(auto it = enemyList.begin(); it != enemyList.end(); it++)
		delete (*it);
	for(auto it = playerBullets.begin(); it != playerBullets.end(); it++)
		delete (*it);
	for (auto it = enemyBullets.begin(); it != enemyBullets.end(); it++) 
		delete (*it);
}


void GameScene::update(sf::RenderWindow& window) {
	float deltaTime = (clock.getElapsedTime() - lastFrameTime).asSeconds();
	lastFrameTime = clock.getElapsedTime();
	if(deltaTime >=.1f){ deltaTime = .1f;};

	//scroll bacgkround "up"
	backgroundOffset += SCREEN_HEIGHT * deltaTime;
	if (backgroundOffset > 512)
		backgroundOffset -= 512;
	backgroundSprite.setPosition(0, backgroundOffset);

	//shooting update
	updateplayershot(window);

	//update bullets
	updateBullets(deltaTime);
	//laser shot
	updateLaser();

	//enemys update
	updateEnemies(deltaTime);


//add enemies to screen if there is none
	if(enemyList.empty())
	{
		if(enemyDisplacement >= SCREEN_HEIGHT)
		{
			enemyDisplacement = 0;
		}else
		{
   			enemyDisplacement += 100;
		}
		enemyList.push_back(new Enemy("media/ball.png", sf::Vector2f(enemyDisplacement , 0)));
		enemyList.push_back(new Enemy("media/ball.png", sf::Vector2f(enemyDisplacement+100, 0)));
	}

	//enemy to player collision
	enemyToPlayerCollision(deltaTime);
	
	//bullet to player collision
	bulletToPlayerCollision(deltaTime);

	//powerup collison
	updateUpgrade();

	updateScoreAndTime();
	player.update(deltaTime);
}

void GameScene::draw(sf::RenderWindow& window) {
	window.draw(backgroundSprite);

	//draw our bullets
	for (auto it = playerBullets.begin(); it != playerBullets.end(); it++) {
		(**it).draw(window);
	}	

	//draw enemy bullets
	for (auto it = enemyBullets.begin(); it != enemyBullets.end(); it++) {
		(**it).draw(window);
	}

	//draw enemies
	for (auto it = enemyList.begin(); it != enemyList.end(); it++) 
	{
		(**it).draw(window);
	}
	player.draw(window);
	testDummy.draw(window);
	printScoreAndTime(window);
}

bool GameScene::handleEvent(sf::Event& event) {
	return false;
}

void GameScene::initializeScoreAndTime()
{
	tempestaSevenFont.loadFromFile("media/pf_tempesta_seven.ttf");
	int offset = 20;
	timer = sf::Text("0:00", tempestaSevenFont, offset);
	//timer.setOrigin(timer.getLocalBounds().width / 2.f, timer.getLocalBounds().height / 2.f);
	timer.setPosition(5, 10);

	scoreStr << scoreNum;
	score = sf::Text(scoreStr.str(), tempestaSevenFont, offset);
	//score.setOrigin(score.getLocalBounds().width / 2.f, score.getLocalBounds().height / 2.f);
	score.setPosition(5, 35);
	scoreStr.str("");
	scoreStr.clear();

	playerhealthStr << healthNum;
	health = sf::Text(playerhealthStr.str(), tempestaSevenFont, offset);
	//score.setOrigin(score.getLocalBounds().width / 2.f, score.getLocalBounds().height / 2.f);
	health.setPosition(5, 55);
	playerhealthStr.str("");
	playerhealthStr.clear();
}

void GameScene::updateScoreAndTime()
{
	int time = clock.getElapsedTime().asSeconds();
	timeStr << "Time: ";
	if(time/60 == 0)
		timeStr << "0:";
	else
	{
		timeStr << time/60 << ":";
		// Get Seconds
		time = time%60;
	}
	if(time < 10)
		timeStr << "0" <<time;
	else
		timeStr << time;

	timer.setString(timeStr.str());
	timeStr.str("");
	timeStr.clear();

	scoreStr << "Score: " << scoreNum;
	score.setString(scoreStr.str());
	scoreStr.str("");
	scoreStr.clear();

	playerhealthStr << "Player HP: " << player.getHealth();
	health.setString(playerhealthStr.str());
	playerhealthStr.str("");
	playerhealthStr.clear();
}

void GameScene::printScoreAndTime(sf::RenderWindow& window)
{
	window.draw(timer);
	window.draw(score);
	window.draw(health);
}

void GameScene::updateplayershot(sf::RenderWindow& window)
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && player.laserShooting == false){
		if((clock.getElapsedTime() - shotTimer).asSeconds() > player.getShotType()->shotTime()){
		//playerBullets.push_back(new Bullet("ball.png", player.pos, sf::Vector2f(0,-400)));
		player.mouseShot(playerBullets, window);
		shotTimer = clock.getElapsedTime();
		}
	}
}

void GameScene::updateBullets(float deltaTime)
{
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
			float thresholdX = abs((**enemyIt).pos.x - (**it).pos.x);
			float thresholdY = abs((**enemyIt).pos.y - (**it).pos.y);
			if(thresholdX < 22.f && thresholdY < 22.f)
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
}

void GameScene::updateLaser()
{
	if(player.laserShooting == true)
	{
		for (auto it = enemyList.begin(); it != enemyList.end(); it++)
		{
			if(player.laser->collidesWith(**it))
			{
				(**it).takeDam(player.laser->dam);
			}
		}
	}
}

void GameScene::updateEnemies(float deltaTime)
{
	for (auto it = enemyList.begin(); it != enemyList.end();) 
	{
		if((**it).isDead())
		{
			scoreNum += 100;

			auto itToErase = it;
			it++;
			delete (*itToErase);
			enemyList.erase(itToErase);
			continue;
		}
		
		(**it).update(deltaTime, enemyBullets, player.pos);
		
		it++;
	}
}

void GameScene::bulletToPlayerCollision(float deltaTime)
{
	for (auto it = enemyBullets.begin(); it != enemyBullets.end();) {
		(**it).update(deltaTime);
		//threshholds for enemy bullet to player collision
		float thresholdX = abs(player.pos.x - (**it).pos.x);
		float thresholdY = abs(player.pos.y - (**it).pos.y);

		//offscreen check
		sf::Vector2f bulletPos = (**it).getPosition();
		if (bulletPos.x < -100 || bulletPos.x > 900 || bulletPos.y < -100 || bulletPos.y > 700 ) {
			auto itToErase = it;
			it++;
			delete (*itToErase);
			enemyBullets.erase(itToErase);
			continue;

			//check for collision
		} else if ( thresholdX < 22 && thresholdY < 22) {
			auto itToErase = it;
			player.damaged((**it).dam);
			it++;
			delete *itToErase;
			enemyBullets.erase(itToErase);

			if(player.isDead())
				SceneManager::getInstance().changeScene("end");

			continue;
		}
		it++;
	}
}

void GameScene::enemyToPlayerCollision(float deltaTime)
{
	if(player.isTargetable())
	{
		for (auto it = enemyList.begin(); it != enemyList.end();) {
		
			//threshholds for enemy bullet to player collision
			float thresholdX = abs(player.pos.x - (**it).pos.x);
			float thresholdY = abs(player.pos.y - (**it).pos.y);

			 if ( thresholdX < 22 && thresholdY < 22) {
				auto itToErase = it;
				player.damaged((**it).collisiondamage());
				player.setTargetable(false);
				hitDelay = clock.getElapsedTime();
				it++;
				continue;
			}
			it++;
		}
	}else
	{
		if((clock.getElapsedTime() - hitDelay ).asSeconds() > 1.0f)
		{
			player.setTargetable(true);
		}
	}
	
	if(player.isDead())
		SceneManager::getInstance().changeScene("end");
}

void GameScene::updateUpgrade()
{
	if(abs(player.pos.x - testDummy.pos.x) < 22 && abs(player.pos.y - testDummy.pos.y) < 22)
	{
		player.powerUP();
		testDummy.setPosition(sf::Vector2f(-100.,-100.));
	}
}