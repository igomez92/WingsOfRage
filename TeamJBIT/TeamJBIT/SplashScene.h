#pragma once

#include "IScene.h"
#include "AnimSprite.h"
#include "dbtweener.h"
#include "Sequence.h"

class SplashScene : public IScene {
	public:
		SplashScene();
		~SplashScene();

		virtual void update(sf::RenderWindow& window);
		virtual void draw(sf::RenderWindow& window);
		virtual bool handleEvent(sf::Event& event);

	private:
		sf::Sprite JBITLogoSprite;
		sf::RectangleShape blackScreen;

		Sequence splashScreenSequence;
		
		sf::Clock clock;
		sf::Time lastFrameTime;
};