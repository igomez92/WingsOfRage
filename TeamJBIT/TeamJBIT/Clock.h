#pragma once

#include <SFML\System.hpp>

class Clock {
	public:
		Clock();

		sf::Time getElapsedTime() const;
		sf::Time restart();

		void pause();
		void resume();

	private:
		sf::Clock internalClock;

		bool isPaused;
		sf::Time lastPauseTime;
		sf::Time pausedDuration;
};
