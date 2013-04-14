#include "SplashScene.h"
#include "SceneManager.h"
#include "TextureManager.h"
#include "Utility.h"

SplashScene::SplashScene() {
	sf::Texture* JBITLogoTexture = _GETTEXTURE("media/UI/JBITLogo.png");
	JBITLogoSprite.setTexture(*JBITLogoTexture);
	centerOrigin(JBITLogoSprite);
	JBITLogoSprite.setPosition(400, 300);
	JBITLogoSprite.setColor(sf::Color::Transparent);

	blackScreen.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	blackScreen.setFillColor(sf::Color::Transparent);

	//sequence the screen
	splashScreenSequence.appendDelay(0.5);
	splashScreenSequence.appendTween(new CDBTweener::CTween(&CDBTweener::TWEQ_QUADRATIC, CDBTweener::TWEA_OUT, 2, 0, [&] (float alpha) {JBITLogoSprite.setColor(sf::Color(255, 255, 255, (sf::Uint8)alpha));}, 255));
	splashScreenSequence.appendDelay(1);
	splashScreenSequence.appendTween(new CDBTweener::CTween(&CDBTweener::TWEQ_QUADRATIC, CDBTweener::TWEA_IN, 2, 255, [&] (float alpha) {JBITLogoSprite.setColor(sf::Color(255, 255, 255, (sf::Uint8)alpha));}, 0));
	splashScreenSequence.appendDelay(1);
	splashScreenSequence.appendTween(new CDBTweener::CTween(&CDBTweener::TWEQ_QUADRATIC, CDBTweener::TWEA_INOUT, 2, 0, [&] (float alpha) {blackScreen.setFillColor(sf::Color(0, 0, 0, (sf::Uint8)alpha));}, 255));
	splashScreenSequence.appendCue([] {SceneManager::getInstance().changeScene("menu");});
}

SplashScene::~SplashScene() {

}

void SplashScene::update(sf::RenderWindow& window) {
	float deltaTime = (clock.getElapsedTime() - lastFrameTime).asSeconds();
	lastFrameTime = clock.getElapsedTime();
	if(deltaTime >=.1f){ deltaTime = .1f;};

	splashScreenSequence.update(deltaTime);
}

void SplashScene::draw(sf::RenderWindow& window) {
	window.clear(sf::Color::White);
	window.draw(JBITLogoSprite);
	window.draw(blackScreen);
}

bool SplashScene::handleEvent(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) {
		SceneManager::getInstance().changeScene("menu", true);
	}

	return false;
}
