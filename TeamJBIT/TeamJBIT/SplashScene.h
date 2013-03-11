#pragma once

#include "IScene.h"
#include "AnimSprite.h"
#include "dbtweener.h"

class SplashScene : public IScene {
	public:
		SplashScene();
		~SplashScene();

		virtual void update(sf::RenderWindow& window);
		virtual void draw(sf::RenderWindow& window);
		virtual bool handleEvent(sf::Event& event);

	private:
		sf::Sprite JBITLogoSprite;
		CDBTweener fadeInTweener;
		
		sf::Clock clock;
		sf::Time lastFrameTime;
};