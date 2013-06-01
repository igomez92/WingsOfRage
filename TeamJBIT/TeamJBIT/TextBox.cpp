#include "TextBox.h"
#include "FontManager.h"
#include "Utility.h"

TextBox::TextBox(std::string text, float timeToShow) {
	captionText = sf::Text(text, *_getFont("media/kimberley bl.ttf"), scaledFontSize(12));
	centerOrigin(captionText);
	captionText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT + 200);

	inOutSequence.appendTween(new CDBTweener::CTween(&CDBTweener::TWEQ_CUBIC, CDBTweener::TWEA_OUT, 1.5, captionText.getPosition().y, [&] (float yPos) {captionText.setPosition(SCREEN_WIDTH / 2, yPos);}, scaledYPos(550)));
	inOutSequence.appendDelay(timeToShow);
	inOutSequence.appendTween(new CDBTweener::CTween(&CDBTweener::TWEQ_CUBIC, CDBTweener::TWEA_IN, 1.5, scaledYPos(550), [&] (float yPos) {captionText.setPosition(SCREEN_WIDTH / 2, yPos);}, SCREEN_HEIGHT + 200));
}

void TextBox::update(float deltaTime) {
	inOutSequence.update(deltaTime);
}

void TextBox::draw(sf::RenderWindow& window) {
	window.draw(captionText);
}

bool TextBox::isDead() {
	return inOutSequence.isEmpty();
}