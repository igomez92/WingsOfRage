#pragma once
#include <cmath>
#include <SFML\System.hpp>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795f
#endif

inline sf::Vector2f normalize(sf::Vector2f in) {
	float len = std::sqrt((in.x*in.x) + (in.y*in.y));
	if (len == 0) return sf::Vector2f(0, 0);
	return in / len;
}