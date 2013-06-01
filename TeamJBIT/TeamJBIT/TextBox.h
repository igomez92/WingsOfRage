#pragma once

#include "IEntity.h"
#include <SFML\Graphics.hpp>
#include "Sequence.h"

class TextBox :  public IEntity {
	public:
		TextBox(std::string text, float timeToShow);
		virtual void update(float deltaTime);
		virtual void draw(sf::RenderWindow& window);
		virtual bool isDead();

	private:
		sf::Text captionText;
		sf::RectangleShape backgroundShape;
		Sequence inOutSequence;
};