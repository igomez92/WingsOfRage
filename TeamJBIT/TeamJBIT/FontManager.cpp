#include "FontManager.h"

sf::Font* FontManager::getFont(std::string fontPath) {
	//do we have it loaded already? if so return a reference
	auto iter = fontMap.begin();
	iter = fontMap.find(fontPath);
	if( iter != fontMap.end() ) {
		return iter->second;
	}

	//if not, load the texture, insert it into the map, and return a reference
	sf::Font* font = new sf::Font();
	font->loadFromFile(fontPath);
	fontMap.insert(std::make_pair(fontPath, font));

	return font;
}