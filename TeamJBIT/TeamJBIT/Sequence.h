#pragma once

#include <deque>
#include <functional>
#include "dbtweener.h"

//a simple sequence that executes tweens one after another, with the possibility for delays in between.
//However, simultaneous or asynchronous tweens are not possible (hence the 'simple')
class Sequence {
	public:
		Sequence();
		void appendTween(CDBTweener::CTween* tween);
		void appendDelay(float delayTime);
		void appendCue(std::function<void ()> cueFunction);
		void update(float deltaTime); //TODO: Consider using sf::Time instead of float in order to prevent drift (consider doing the same to AnimSprite)

	private:
		std::deque<CDBTweener::CTween*> tweenQueue;
};