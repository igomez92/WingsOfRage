#pragma once

#include "IScene.h"
#include "AnimSprite.h"
#include "dbtweener.h"
#include "Button.h"

class MenuScene : public IScene {
	public:
		MenuScene();
		~MenuScene();

		virtual void update(sf::RenderWindow& window);
		virtual void draw(sf::RenderWindow& window);
		virtual bool handleEvent(sf::Event& event);

	private:
		sf::Sprite gameLogoSprite;
		sf::Sprite backgroundSprite;
		float backgroundScroll;

		TextButton* buttons [3];
		bool shouldQuit; //ugh
		
		sf::Clock clock;
		sf::Time lastFrameTime;
};
