#pragma once

#include <SFML\Graphics.hpp>
#include <functional>

class Button {
	public:
		Button();
		Button(sf::FloatRect& boundsRect, std::function<void()> onPressFunction = [] {});
		~Button();
		void processClick(sf::Event event);

		std::function<void ()> onPressFunction;
		sf::FloatRect boundsRect;		
};

class TextButton : public Button {
	public:
		TextButton();
		TextButton(sf::FloatRect& boundsRect, std::string label, float fontSize, std::function<void()> onPressFunction = [] {});
		~TextButton();
		sf::Text labelText;

	private:
};
