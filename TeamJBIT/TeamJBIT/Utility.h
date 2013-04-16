#pragma once

#include <cmath>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795f
#endif

inline float scaledFontSize(float oldSize) {
	return oldSize * (SCREEN_WIDTH / 800.f);
}

inline float scaledXPos(float oldXPos) {
	return oldXPos * (SCREEN_WIDTH / 800.f);
}

inline float scaledYPos(float oldYPos) {
	return oldYPos * (SCREEN_HEIGHT / 600.f);
}

inline sf::Vector2f scaledPos(sf::Vector2f& oldPos) {
	return sf::Vector2f(scaledXPos(oldPos.x), scaledYPos(oldPos.y));
}

inline float deg2rad(float degrees) {
	return degrees * (M_PI / 180.f);
}

inline float rad2deg(float rad) {
	return rad * (180.f / M_PI);
}

inline float vecLen2(sf::Vector2f in) {
	return (in.x * in.x) + (in.y * in.y);
}

inline float vecLen(sf::Vector2f in) {
	return std::sqrtf((in.x * in.x) + (in.y * in.y));
}

inline sf::Vector2f normalize(sf::Vector2f in) {
	float len = vecLen(in);
	if (len == 0) return sf::Vector2f(0, 0);
	return in / len;
}

inline void centerOrigin(sf::Sprite& sprite) {
	sprite.setOrigin((int)sprite.getLocalBounds().width / 2, (int)sprite.getLocalBounds().height / 2);
}

inline void centerOrigin(sf::Text& text) {
	text.setOrigin((int)text.getLocalBounds().width / 2, (int)text.getLocalBounds().height / 2);
}
