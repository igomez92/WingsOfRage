#include "EndGameScene.h"
#include <cmath>
#include <SFML\System.hpp>

EndGameScene::EndGameScene()  {
	tempestaSevenFont.loadFromFile("pf_tempesta_seven.ttf");
	gameOverMessage = sf::Text("GAME OVER", tempestaSevenFont, 100);
	gameOverMessage.setOrigin(gameOverMessage.getLocalBounds().width / 2.f, gameOverMessage.getLocalBounds().height / 2.f);
	gameOverMessage.setPosition(400, 300);
}

EndGameScene::~EndGameScene() {

}

void EndGameScene::update() {
	float deltaTime = (clock.getElapsedTime() - lastFrameTime).asSeconds();
	lastFrameTime = clock.getElapsedTime();

	gameOverMessage.setRotation(std::sinf(clock.getElapsedTime().asSeconds()));
}

void EndGameScene::draw(sf::RenderWindow& window) {
	window.draw(gameOverMessage);
}

bool EndGameScene::handleEvent(sf::Event& event) {
	return false;
}