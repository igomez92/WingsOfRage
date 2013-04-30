#include "GameScene.h"
#include "SceneManager.h"
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "FontManager.h"
#include "MeleeEnemy.h"
#include "CircleEnemy.h"
#include "SpiralEnemy.h"

GameScene::GameScene() : player( sf::Vector2f(400, 300)), scoreNum(0) , powerUp("media/PowerUp.png", sf::Vector2f(-100,-100)), backgroundOffsetLow(0), backgroundOffsetMed(0), numOfBombs(3), bombDelay(5.0f),
currBombTime(0.0f),bombRunning(false), bombWait(0.0f),bombReady(true) 
{
	// Initialize score info
	initializeScoreAndTime();

	enemySpawnQueue = LevelLoader::loadLevel("media/levels/level 1.txt");
	bossSpawned = false;

	sf::Texture* bgImage = _getTexture("media/backgrounds/starsLow.png");
	bgImage->setRepeated(true);
	backgroundSpriteLow.setTexture(*bgImage);
	backgroundSpriteLow.setTextureRect(sf::IntRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT * 2));
	backgroundSpriteLow.setOrigin(0, SCREEN_HEIGHT);

	bgImage = _getTexture("media/backgrounds/starsMed.png");
	bgImage->setRepeated(true);
	backgroundSpriteMed.setTexture(*bgImage);
	backgroundSpriteMed.setTextureRect(sf::IntRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT * 2));
	backgroundSpriteMed.setOrigin(0, SCREEN_HEIGHT);
}

GameScene::~GameScene() 
{
	if(bombRunning)
	{
		delete bomb;
	}

	for(auto it = enemyList.begin(); it != enemyList.end(); it++)
		delete (*it);
	for(auto it = playerBullets.begin(); it != playerBullets.end(); it++)
		delete (*it);
	for (auto it = enemyBullets.begin(); it != enemyBullets.end(); it++) 
		delete (*it);
	for (auto it = allParticles.begin(); it != allParticles.end(); it++)
		delete (*it);
}


void GameScene::update(sf::RenderWindow& window) {
	float deltaTime = (clock.getElapsedTime() - lastFrameTime).asSeconds();
	lastFrameTime = clock.getElapsedTime();
	if(deltaTime >=.1f){ deltaTime = .1f;};

	//scroll bacgkround "up"
	backgroundOffsetLow += 320 * deltaTime;
	if (backgroundOffsetLow > 512)
		backgroundOffsetLow -= 512;
	backgroundSpriteLow.setPosition(0, backgroundOffsetLow);
	backgroundOffsetMed += 400 * deltaTime;
	if (backgroundOffsetMed > 512)
		backgroundOffsetMed -= 512;
	backgroundSpriteMed.setPosition(0, backgroundOffsetMed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && numOfBombs != 0 && !bombRunning && bombReady)
	{
		startBomb();
	}
	else if(!bombReady)
	{
		bombWait += deltaTime;

		if(bombWait >= bombDelay)
		{
			bombReady = true;
			bombWait = 0.0f;
		}
	}


	//shooting update
	updateplayershot(window);
	
	//update bullets
	updatePlayerBullets(deltaTime);

	//laser shot
	updateLaser();

	// sword swing
	updateSword();

	//enemies update
	updateEnemies(deltaTime);

	// particle effects
	updateParticleEffects(deltaTime);

	//spawn enemies if it's time
	updateSpawnQueue();

	// Update if we are using a bomb
	updateBomb(deltaTime, enemyList);

	//if no more enemies summon a boss
	if(enemyList.empty() && !bossSpawned && enemySpawnQueue.empty())
	{
		enemyList.push_back(new Boss1("media/ball.png", sf::Vector2f(100, 0)));
		bossSpawned = true;
	}else if(enemyList.empty() && bossSpawned)
	{
		SceneManager::getInstance().changeScene("end");
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
	window.draw(backgroundSpriteLow);
	window.draw(backgroundSpriteMed, sf::RenderStates(sf::BlendAdd));

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

	//draw particles
	for (auto it = allParticles.begin(); it!= allParticles.end(); it++)
	{
		(**it).draw(window);
	}

	player.draw(window);
	powerUp.draw(window);
	printScoreAndTime(window);
}

bool GameScene::handleEvent(sf::Event& event) {
	return false;
}

void GameScene::initializeScoreAndTime()
{
	int offset = 20;
	timer = sf::Text("0:00", *_getFont("media/pf_tempesta_seven.ttf"), offset);
	//timer.setOrigin(timer.getLocalBounds().width / 2.f, timer.getLocalBounds().height / 2.f);
	timer.setPosition(5, 10);

	scoreStr << scoreNum;
	score = sf::Text(scoreStr.str(), *_getFont("media/pf_tempesta_seven.ttf"), offset);
	//score.setOrigin(score.getLocalBounds().width / 2.f, score.getLocalBounds().height / 2.f);
	score.setPosition(5, 35);
	scoreStr.str("");
	scoreStr.clear();

	playerhealthStr << healthNum;
	health = sf::Text(playerhealthStr.str(), *_getFont("media/pf_tempesta_seven.ttf"), offset);
	//score.setOrigin(score.getLocalBounds().width / 2.f, score.getLocalBounds().height / 2.f);
	health.setPosition(5, 60);
	playerhealthStr.str("");
	playerhealthStr.clear();
}

void GameScene::updateScoreAndTime()
{
	int time = clock.getElapsedTime().asSeconds();
	timeStr << "Time: ";
	if (time / 60 == 0)
		timeStr << "0:";
	else
	{
		timeStr << time / 60 << ":";
		// Get Seconds
		time = time % 60;
	}
	if (time < 10)
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


	if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && player.laserShooting == false){
		if(player.currentPlayerMode == GUNNER_MODE && player.canBlink)
		{
			float distanceToBlink = 400;
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			sf::Vector2f dir;
			dir.x = (float)mousePos.x - player.pos.x;
			dir.y = (float)mousePos.y - player.pos.y;
			float length = vecLen(dir);
			dir = normalize(dir);
			if(length <= distanceToBlink)
			{
				distanceToBlink = length;
			}
			dir = distanceToBlink*dir;
			sf::Vector2f blinkLocation;
			blinkLocation = player.pos + dir;

			if(blinkLocation.x >= SCREEN_WIDTH)
			{
				blinkLocation.x = SCREEN_WIDTH - player.sprite.getFrameSize().x;
			}
			if(blinkLocation.x < 0)
			{
				blinkLocation.x = 0 + player.sprite.getFrameSize().x;
			}
			if(blinkLocation.y >= SCREEN_HEIGHT)
			{
				blinkLocation.y = SCREEN_HEIGHT - player.sprite.getFrameSize().y;
			}
			if(blinkLocation.y < 0)
			{
				blinkLocation.y = 0 + player.sprite.getFrameSize().y;
			}	
			player.pos = blinkLocation;
			blinkDelay = clock.getElapsedTime();
			player.canBlink = false;
		}
		else if((clock.getElapsedTime() - blinkDelay).asSeconds() >.2)
		{
			player.canBlink = true;
		}
	}

}

void GameScene::updatePlayerBullets(float deltaTime)
{
	for (auto it = playerBullets.begin(); it != playerBullets.end();) {
		(**it).update(deltaTime);

		//offscreen check
		sf::Vector2f bulletPos = (**it).getPosition();
		if (bulletPos.x < -100 || bulletPos.x > SCREEN_WIDTH + 100 || bulletPos.y < -100 || bulletPos.y > SCREEN_HEIGHT + 100) {
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
				//if enemy is a reflecting type then reflect the bullet instead of taking damage
				
				if((**enemyIt).type == Reflector)
				{
					if((**it).dam >= 500)
					{
						(**enemyIt).takeDam((**it).dam);
					}
					sf::Vector2f aiming;
					aiming = (-(**it).vel);
					aiming = aiming * .25f;
					enemyBullets.push_back(new Bullet("media/bullet.png", (**it).pos ,aiming, 5, sf::Color(255, 50, 50)));
					
				}
				else
				{
					(**enemyIt).takeDam((**it).dam);
				}
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

void GameScene::updateSword()
{
	if(player.swordSwinging == true)
	{
		for (auto it = enemyList.begin(); it != enemyList.end(); it++)
		{
			if(player.sword->collidesWith(**it))
			{
				(**it).takeDam(player.sword->dam);
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
			if(scoreNum % 400 == 0)
			{
				powerUp.setPosition((**it).pos);
				if(player.powerUpFound)
					powerUp.isHP = true;
			}
			ptManager.doExplosion(allParticles, (**it).pos, sf::Color::Green, 100.0);
			auto itToErase = it;
			it++;
			delete (*itToErase);
			enemyList.erase(itToErase);
			continue;
		}
		
		(**it).update(deltaTime, enemyBullets, playerBullets, player);
		
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
		if (bulletPos.x < -100 || bulletPos.x > SCREEN_WIDTH + 100 || bulletPos.y < -100 || bulletPos.y > SCREEN_HEIGHT + 100 ) {
			auto itToErase = it;
			it++;
			delete (*itToErase);
			enemyBullets.erase(itToErase);
			continue;

			//check for collision
		} else if ( thresholdX < 22 && thresholdY < 22) {
			auto itToErase = it;
			player.damaged((**it).dam);
			ptManager.doHitParticle(allParticles, player.pos, (**it).vel, sf::Color::Magenta, 75.0);
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
	if(abs(player.pos.x - powerUp.pos.x) < 22 && abs(player.pos.y - powerUp.pos.y) < 22)
	{
		if(!player.powerUpFound)
			player.powerUP();
		else
			player.increaseHealth(100);
		powerUp.setPosition(sf::Vector2f(-100.,-100.));
	}
}

void GameScene::updateSpawnQueue() 
{
	if (enemySpawnQueue.empty()) return;

	float time = clock.getElapsedTime().asSeconds();

	while (!enemySpawnQueue.empty() && enemySpawnQueue.front().spawnTime < time) {
		LevelLoader::spawnEnemy(enemyList, enemySpawnQueue.front());
		enemySpawnQueue.pop();
	}
}

void GameScene::updateParticleEffects(float deltaTime)
{
	
	for (auto it = allParticles.begin(); it != allParticles.end();) 
	{
		(**it).update(deltaTime);
		float thresholdX = abs((**it).startingPosition.x - (**it).pos.x);
		float thresholdY = abs((**it).startingPosition.y - (**it).pos.y);
		//offscreen check
		if (thresholdY > (**it).lifeExpectancy || 
			thresholdX > (**it).lifeExpectancy) 
		{
			auto itToErase = it;
			it++;
			delete (*itToErase);
			allParticles.erase(itToErase);
			continue;
		}
		it++;
	}
	ptManager.doEnginePartcle(allParticles, player.pos, sf::Color::Color(0, 255, 208, 255), 50.0);
}

void GameScene::startBomb()
{
	bomb = new SuperBomb();
	numOfBombs--;
	bombRunning = true;
}

void GameScene::updateBomb(float deltaTime, std::list<Enemy*> enemList)
{
	if(bombRunning)
	{
		currBombTime += deltaTime;
		if(currBombTime < bomb->runTime)
		{
			if(bomb->damDone == false)
			{
				for(auto it = enemList.begin(); it != enemList.end(); it++)
				{
					bomb->checkForDestruction(**it);
				}
			}
		}
		else
		{
			bomb->finishedDamagePhase();
		}

		if(bomb->hasFinished)
		{
			delete bomb;
			bombRunning = false;
			bombReady = false;
			currBombTime = 0.0;
		}
	}
}
