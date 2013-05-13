#include "Clock.h"

Clock::Clock() : isPaused(false) {

}

sf::Time Clock::getElapsedTime() const {
	if (isPaused) {
		return lastPauseTime - pausedDuration;
	} else {
		return internalClock.getElapsedTime() - pausedDuration;
	}
}

sf::Time Clock::restart() {
	sf::Time elapsed = getElapsedTime();

	pausedDuration = sf::Time::Zero;
	lastPauseTime = sf::Time::Zero;
	internalClock.restart();
	isPaused = false;

	return elapsed;
}

void Clock::pause() {
	if (isPaused) return;

	isPaused = true;
	lastPauseTime = internalClock.getElapsedTime();
}

void Clock::resume() {
	if (!isPaused) return;

	isPaused = false;
	pausedDuration += (internalClock.getElapsedTime() - lastPauseTime);
}
