#pragma once
#include <cmath>
#include <SFML\System.hpp>

inline sf::Vector2f normalize(sf::Vector2f in) {
	float len = std::sqrt((in.x*in.x) + (in.y*in.y));
	return in / len;
}