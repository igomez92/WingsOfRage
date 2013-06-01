#include "GameScene.h"
#include "SceneManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TextureManager.h"
#include "FontManager.h"
#include "MeleeEnemy.h"
#include "CircleEnemy.h"
#include "SpiralEnemy.h"
#include <tuple>

GameScene::GameScene() : player( sf::Vector2f(400, 300)), scoreNum(0), backgroundOffsetLow(0), backgroundOffsetMed(0), numOfBombs(3), bombDelay(5.0f),
currBombTime(0.0f),bombRunning(false), bombWait(0.0f),bombReady(true), energyDecreaseDone(false), totalPowerTime(10.0f), currentPowerTime(0.0f), mousePressed(false)
{
	sManager.setMusic("media/crazy.ogg");
	sManager.playMusic();
	// Initialize score info
	initializeScoreAndTime();

	entitySpawnQueue = LevelLoader::loadLevel("media/levels/testlevel.txt");
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

	sf::Texture* health = _getTexture("media/HealthBar.png");
	healthBar.setTexture(*health);
	healthBar.setOrigin(0, healthBar.getLocalBounds().height/2);
	healthBar.setPosition(10, 100);
	healthBar.setColor(sf::Color(255, 255, 255, 160));

	sf::Texture* energy = _getTexture("media/EnergyBar.png");
	energyBar.setTexture(*energy);
	energyBar.setOrigin(0, energyBar.getLocalBounds().height/2);
	energyBar.setPosition(10, 125);
	energyBar.setColor(sf::Color(255, 255, 255, 160));

	sf::Texture* power = _getTexture("media/PowerBar.png");
	powerBar.setTexture(*power);
	powerBar.setOrigin(0, powerBar.getLocalBounds().height/2);
	powerBar.setPosition(10, 150);
	powerBar.setColor(sf::Color(255, 255, 255, 160));

	sf::Texture* bomb = _getTexture("media/bombTemp.png");
	bombImage.setTexture(*bomb);
	bombImage.setOrigin(bombImage.getLocalBounds().width/2, bombImage.getLocalBounds().height/2);
	bombImage.setPosition(1175, 55);
	bombImage.setColor(sf::Color(255, 255, 255, 160));
	bombText.setPosition(1200, 50);
	bombText.setColor(sf::Color(255, 255, 255, 160));
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
	for (auto it = powerUps.begin(); it != powerUps.end(); it++)
		delete (*it);
}

void GameScene::enter() {
	clock.resume();
	sManager.playMusic();
}

void GameScene::leave() {
	clock.pause();
	sManager.stopMusic();
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

	//update all entities
	for (auto it = entityList.begin(); it != entityList.end();) {
		(**it).update(deltaTime);

		if ((**it).isDead()) {
			auto itToErase = it;
			it++;
			delete (*itToErase);
			entityList.erase(itToErase);
			continue;
		}
		it++;
	}

	updateHealthAndEnergy();

	//if no more enemies summon a boss
	if(enemyList.empty() && !bossSpawned && entitySpawnQueue.empty())
	{
		enemyList.push_back(new Boss1("media/ball.png", sf::Vector2f(100, 0)));
		bossSpawned = true;
	}else if(enemyList.empty() && bossSpawned)
	{
		//SceneManager::getInstance().changeScene("end");
		SceneManager::getInstance().changeScene("win");
	}

	//enemy to player collision
	enemyToPlayerCollision(deltaTime);
	
	//bullet to player collision
	bulletToPlayerCollision(deltaTime);

	//powerup collison
	updateUpgrade();

	updateScoreAndTime();

	if(player.powerUpFound)
	{
		currentPowerTime += deltaTime;
	}
	if(currentPowerTime > totalPowerTime)
	{
		currentPowerTime = 0.0f;
		player.powerUpFound = false;
	}

	player.update(deltaTime, playerBullets);
	
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

	//draw upgrades
	for (auto it = powerUps.begin(); it != powerUps.end(); it++)
	{
		(**it).draw(window);
	}

	for (IEntity* ent : entityList) {
		ent->draw(window);
	}

	player.draw(window);
	printScoreAndTime(window);
	window.draw(healthBar);
	window.draw(energyBar);
	window.draw(powerBar);
	window.draw(bombText);
	window.draw(bombImage);
}

bool GameScene::handleEvent(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		SceneManager::getInstance().changeScene("pause");
		return true;
	}

	return false;
}

void GameScene::initializeScoreAndTime()
{
	int offset = 20;
	timer = sf::Text("0:00", *_getFont("media/pf_tempesta_seven.ttf"), offset);
	//timer.setOrigin(timer.getLocalBounds().width / 2.f, timer.getLocalBounds().height / 2.f);
	timer.setPosition(5, 10);
	timer.setColor(sf::Color(255, 255, 255, 160));

	scoreStr << scoreNum;
	score = sf::Text(scoreStr.str(), *_getFont("media/pf_tempesta_seven.ttf"), offset);
	//score.setOrigin(score.getLocalBounds().width / 2.f, score.getLocalBounds().height / 2.f);
	score.setPosition(5, 35);
	scoreStr.str("");
	scoreStr.clear();
	score.setColor(sf::Color(255, 255, 255, 160));

	playerhealthStr << healthNum;
	health = sf::Text(playerhealthStr.str(), *_getFont("media/pf_tempesta_seven.ttf"), offset);
	//score.setOrigin(score.getLocalBounds().width / 2.f, score.getLocalBounds().height / 2.f);
	health.setPosition(5, 60);
	playerhealthStr.str("");
	playerhealthStr.clear();
	health.setColor(sf::Color(255, 255, 255, 160));

	bombStream << " X " << numOfBombs;
	bombText = sf::Text(bombStream.str(), *_getFont("media/pf_tempesta_seven.ttf"), offset);
	bombStream.str("");
	bombStream.clear();
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

	bombStream << " X " << numOfBombs;
	bombText.setString(bombStream.str());
	bombStream.str("");
	bombStream.clear();
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
			player.mouseShot(playerBullets, window, mousePressed);
			shotTimer = clock.getElapsedTime();
		}
	}
	
	if(sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mousePressed = true;
	}
	else if(sf::Event::MouseButtonReleased)
	{
		mousePressed = false;
	}


	if(player.isDoingABarrelRoll == false)
	{
		energyDecreaseDone = false;
	}


	if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && player.laserShooting == false){
		if(player.currentPlayerMode == GUNNER_MODE && player.canBlink && player.getEnergy() != 0)
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
			player.decreaseEnergy(100);
		}
		else if((clock.getElapsedTime() - blinkDelay).asSeconds() > .2)
		{
			player.canBlink = true;
		}
	}

	if(player.currentPlayerMode == PLANE_MODE && sf::Mouse::isButtonPressed(sf::Mouse::Right) && player.getEnergy() != 0)
	{
		if (player.pos.x < sf::Mouse::getPosition(window).x)
		{
			//press Z or R twice
			player.doABarrelRoll(false); //true if left, false if right
		}
		else
		{
			player.doABarrelRoll(true);
		}

		if(energyDecreaseDone == false)
		{
			player.decreaseEnergy(100);
			energyDecreaseDone = true;
		}
	}

	if(player.currentPlayerMode == FIGHTER_MODE && sf::Mouse::isButtonPressed(sf::Mouse::Right) && player.getEnergy() != 0)
	{
		player.setShieldUp(true);
		player.decreaseEnergy(1);
	}else
	{
		player.setShieldUp(false);
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
					if((**it).dam >= 100)
					{
						(**enemyIt).takeDam((**it).dam);
					}
					sf::Vector2f aiming;
					aiming = (-(**it).vel);
					aiming = aiming * .8f;
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
				if((**it).type != EnemyType::Boss)
					(**it).takeDam(player.laser->dam);
				else
					(**it).takeDam(player.laser->dam/10);
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
				powerUps.push_back(new PowerUp((**it).pos));
				//powerUp.setPosition((**it).pos);
				//if(player.powerUpFound)
					//powerUp.isHP = true;
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

			//if barrel rolling reflect bullets
			if (player.isDoingABarrelRoll)
			{
				sf::Vector2f aiming;
				aiming = (-(**it).vel);
				//aiming = aiming * .25f;
				playerBullets.push_back(new Bullet("media/bullet.png", (**it).pos ,aiming, 5));	
			}			
			if (player.isShieldUp() && !player.isDoingABarrelRoll)
			{
				if(player.getEnergy() == 0)
				{
					player.damaged((**it).dam);
				}
			}

			//should we apply damage
			if (!player.isShieldUp() && !player.isDoingABarrelRoll)
			{
				player.damaged((**it).dam);
			}

			if (!player.isDoingABarrelRoll)
			{
				ptManager.doHitParticle(allParticles, player.pos, (**it).vel, sf::Color::Magenta, 75.0);
			}

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

			if ( thresholdX < 22 && thresholdY < 22 && player.isShieldUp() == false) {
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
	for(auto it = powerUps.begin(); it != powerUps.end();)
	{
		if(abs(player.pos.x - (**it).pos.x) < 22 && abs(player.pos.y - (**it).pos.y) < 22)
		{
			int upgradeType = (**it).getUpgradeType();
			if(upgradeType == WEAPON_UPGRADE)
				player.powerUP();
			else if(upgradeType == HEALTH_UPGRADE)
				player.increaseHealth(100);
			else
				player.increaseEnergy(100);

			auto itToErase = it;
			it++;
			delete (*itToErase);
			powerUps.erase(itToErase);
			continue;
		}
		it++;
	}
}

void GameScene::updateSpawnQueue() 
{
	if (entitySpawnQueue.empty()) return;

	float time = clock.getElapsedTime().asSeconds();

	while (!entitySpawnQueue.empty() && entitySpawnQueue.front().spawnTime < time) {
		spawnEntity(entitySpawnQueue.front());

		if (entitySpawnQueue.front().data != nullptr)
			delete entitySpawnQueue.front().data;
		entitySpawnQueue.pop();
	}
}

void GameScene::spawnEntity(LevelLoader::EntitySpawnEntry& entry) 
{
	switch (entry.entityType)
	{
		case LevelLoader::EntitySpawnType::INVALID:
			break;

		/////

		case LevelLoader::EntitySpawnType::TEXTBOX: {
			std::tuple<std::string, float> textBoxData = *((std::tuple<std::string, float>*)(entry.data));
			entityList.push_back(new TextBox(std::get<0>(textBoxData), std::get<1>(textBoxData)));
			} break;

		/////

		case LevelLoader::EntitySpawnType::ENEMY:
			enemyList.push_back(new Enemy("media/drone.png", scaledPos(sf::Vector2f(entry.xPos, entry.yPos))));
			break;

		case LevelLoader::EntitySpawnType::TANKENEMY:
			enemyList.push_back(new TankEnemy("media/baller.png", scaledPos(sf::Vector2f(entry.xPos, entry.yPos))));
			break;

		case LevelLoader::EntitySpawnType::MTANKENEMY:
			enemyList.push_back(new MTankEnemy("media/mballer.png", scaledPos(sf::Vector2f(entry.xPos, entry.yPos))));
			break;

		case LevelLoader::EntitySpawnType::SLIDERENEMY:
			enemyList.push_back(new SliderEnemy("media/slider.png", scaledPos(sf::Vector2f(entry.xPos, entry.yPos))));
			break;

		case LevelLoader::EntitySpawnType::CIRCLEENEMY:
			enemyList.push_back(new CircleEnemy("media/turret.png", scaledPos(sf::Vector2f(entry.xPos, entry.yPos))));
			break;

		case LevelLoader::EntitySpawnType::MELEEENEMY:
			enemyList.push_back(new MeleeEnemy("media/knight.png", scaledPos(sf::Vector2f(entry.xPos, entry.yPos))));
			break;

		case LevelLoader::EntitySpawnType::SPIRALENEMY:
			enemyList.push_back(new SpiralEnemy("media/turret.png", scaledPos(sf::Vector2f(entry.xPos, entry.yPos))));
			break;
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

void GameScene::updateHealthAndEnergy()
{
	float healthScale = (float) player.getHealth()/player.getTotalHealth();
	healthBar.setScale(healthScale, 1);

	float energyScale = (float) player.getEnergy()/player.getTotalHealth();
	energyBar.setScale(energyScale, 1);


	if(currentPowerTime != 0.0f)
	{
		float powerScale = (totalPowerTime-currentPowerTime)/totalPowerTime;
		powerBar.setScale(powerScale, 1);
	}
	else
	{
		powerBar.setScale(0, 1);
	}
}