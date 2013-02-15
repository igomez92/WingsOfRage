#include "GameScene.h"

GameScene::GameScene() : player("ball.png", 400, 300), enemy("ball.png", 300, 50) {

}

GameScene::~GameScene() {

}
	
void GameScene::update() {
	enemy.update();
	player.update();
}

void GameScene::draw(sf::RenderWindow& window) {
	window.draw(player.getSprite());
	window.draw(enemy.getSprite());
}

bool GameScene::handleEvent(sf::Event& event) {
	return false;
}