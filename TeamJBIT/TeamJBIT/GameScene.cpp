#include "GameScene.h"

GameScene::GameScene() : player("ball.png", sf::Vector2f(400, 300)), enemy("ball.png", sf::Vector2f(300, 50)) {

}

GameScene::~GameScene() {

}
	
void GameScene::update() {
	float deltaTime = clock.getElapsedTime().asSeconds() - lastFrameTime.asSeconds();
	lastFrameTime = clock.getElapsedTime();


	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		playerBullets.push_back(Bullet("ball.png", player.pos, sf::Vector2f(0,-400)));
	}

	//update bullets
	for (auto it = playerBullets.begin(); it != playerBullets.end();) {
		it->update(deltaTime);

		//offscreen check
		if (it->getPosition().y < -100) {
			auto itToErase = it;
			it++;
			playerBullets.erase(itToErase);
			continue;
		}

		it++;
	}

	enemy.update(deltaTime);
	player.update(deltaTime);
}

void GameScene::draw(sf::RenderWindow& window) {
	//draw bullets
	for (auto it = playerBullets.begin(); it != playerBullets.end(); it++) {
		it->draw(window);
	}

	enemy.draw(window);
	player.draw(window);
}

bool GameScene::handleEvent(sf::Event& event) {
	return false;
}