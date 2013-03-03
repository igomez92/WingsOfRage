//Animated Sprite header

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

class AnimSprite : public sf::Sprite {
	public:
		AnimSprite();
		void setFrameSize(int width, int height);
		void setBorderSize(int width, int height);
		void update(float frameTime);
		void showFrame(unsigned int frameNum);
		void addAnim(std::string name, int startX = 0, int startY = 0, int numFrames = 1, int numPerRow = 1, float framerate = 1, bool isCyclic = true);
		bool playAnim(std::string name);

	protected:
		struct AnimSprAnimation {
			std::string name;
			int numFrames;
			int numPerRow;
			sf::Vector2i startPos;
			float framerate;
			bool isCyclic;
		};

		sf::Vector2i frameSize;
		sf::Vector2i borderSize;
		float timeSinceLastFrame;
		int currentFrame;
		std::map<std::string, AnimSprAnimation*> AnimsList;
		AnimSprAnimation *currentAnim;
};