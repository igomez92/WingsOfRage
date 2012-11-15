#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include <SFML/Graphics.hpp>

enum AnimationType
{
	RUNNING_RIGHT,
	RUNNING_LEFT,
	STANDING_RIGHT,
	STANDING_LEFT
};

class Animation
{
public:
	Animation();
	Animation(AnimationType type);
	~Animation();
	sf::Sprite getSprite();
	void update(int x, int y);
	void reset();
private:
	AnimationType animationType;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Clock animationClock;
	std::vector<sf::IntRect> spriteRects;
	int animationTime;
	int spriteIndex;
	void createRects();
};

#endif