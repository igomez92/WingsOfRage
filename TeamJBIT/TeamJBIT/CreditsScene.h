#pragma once

#include "IScene.h"
#include "AnimSprite.h"
#include "dbtweener.h"
#include "Button.h"

class CreditsScene : public IScene {
	public:
		CreditsScene();
		~CreditsScene();

		virtual void update(sf::RenderWindow& window);
		virtual void draw(sf::RenderWindow& window);
		virtual bool handleEvent(sf::Event& event);

	private:
		sf::Sprite backgroundSprite;
		float backgroundScroll;
		sf::RectangleShape blackScreen;

		sf::Text teamLabel;
		sf::Text teamList;

		TextButton backButton;

		CDBTweener fadeTweener;
		
		sf::Clock clock;
		sf::Time lastFrameTime;
};
