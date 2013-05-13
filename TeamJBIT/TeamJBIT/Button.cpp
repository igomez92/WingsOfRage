#include "Button.h"
#include "Utility.h"
#include "FontManager.h"

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

	labelText = sf::Text(label, *_getFont("media/kimberley bl.ttf"), fontSize);
	centerOrigin(labelText);
	labelText.setPosition(boundsRect.left + (boundsRect.width / 2), boundsRect.top + (boundsRect.height / 2));
}

TextButton::~TextButton() {

}

void TextButton::setSelected()
{
	labelText.setColor(sf::Color::Yellow);
}

void TextButton::setUnselected()
{
	labelText.setColor(sf::Color::White);
}