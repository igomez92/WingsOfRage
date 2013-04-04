#include "Button.h"
#include "Utility.h"

Button::Button() {
	onPressFunction = [] {};
}

Button::Button(sf::FloatRect& boundsRect, std::function<void()> onPressFunction) {
	this->onPressFunction = onPressFunction;
	this->boundsRect = boundsRect;
}

Button::~Button() {

}

void Button::processClick(sf::Event event) {
	if (boundsRect.contains(event.mouseButton.x, event.mouseButton.y)) {
		onPressFunction();
	}
}

TextButton::TextButton() {
	onPressFunction = [] {};
}

TextButton::TextButton(sf::FloatRect& boundsRect, std::string label, float fontSize, std::function<void()> onPressFunction) {
	this->onPressFunction = onPressFunction;
	this->boundsRect = boundsRect;

	tempestaSevenFont.loadFromFile("media/pf_tempesta_seven.ttf");

	labelText = sf::Text(label, tempestaSevenFont, fontSize);
	centerOrigin(labelText);
	labelText.setPosition(boundsRect.left + (boundsRect.width / 2), boundsRect.top + (boundsRect.height / 2));
}

TextButton::~TextButton() {

}
