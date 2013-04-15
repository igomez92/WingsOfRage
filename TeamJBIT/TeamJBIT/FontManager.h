#pragma once

#include <SFML\Graphics.hpp>
#include <map>

class FontManager {
	public:
		static FontManager& getInstance() {
			static FontManager instance;
			return instance;
		}
		sf::Font* getFont(std::string fontPath);

	private:
		FontManager() {};
		~FontManager() {};
		FontManager(const FontManager&);
		FontManager& operator =(const FontManager&);

		std::map<std::string, sf::Font*> fontMap;
};

inline sf::Font* _getFont(std::string path) {
	return FontManager::getInstance().getFont(path);
}
