#include "SplashScene.h"
#include "SceneManager.h"
#include "TextureManager.h"

SplashScene::SplashScene() {
	sf::Texture* JBITLogoTexture = TextureManager::getInstance().getTexture("media/UI/JBITLogo.png");
	JBITLogoSprite.setTexture(*JBITLogoTexture);
	JBITLogoSprite.setOrigin((int)JBITLogoSprite.getLocalBounds().width / 2, (int)JBITLogoSprite.getLocalBounds().height / 2);
	JBITLogoSprite.setPosition(400, 300);

	//fade in
	fadeInTweener.addTween(&CDBTweener::TWEQ_QUADRATIC, CDBTweener::TWEA_OUT, 2, 0, [&] (float alpha) {JBITLogoSprite.setColor(sf::Color(255, 255, 255, (sf::Uint8)alpha));}, 255);
}

SplashScene::~SplashScene() {

}

void SplashScene::update(sf::RenderWindow& window) {
	float deltaTime = (clock.getElapsedTime() - lastFrameTime).asSeconds();
	lastFrameTime = clock.getElapsedTime();
	if(deltaTime >=.1f){ deltaTime = .1f;};

	fadeInTweener.step(deltaTime);
}

void SplashScene::draw(sf::RenderWindow& window) {
	window.clear(sf::Color::White);
	window.draw(JBITLogoSprite);
}

bool SplashScene::handleEvent(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		SceneManager::getInstance().changeScene("start", true);
	}

	return false;

}