#include "Sequence.h"

Sequence::Sequence() {
}

void Sequence::appendTween(CDBTweener::CTween* tween) {
	tweenQueue.push_back(tween);
}

void Sequence::appendDelay(float delayTime) {
	//do-nothing tween with duration equal to desired delay
	tweenQueue.push_back(new CDBTweener::CTween(&CDBTweener::TWEQ_LINEAR, CDBTweener::TWEA_IN, delayTime, 0, [] (float) {}, 0));
}

void Sequence::appendCue(std::function<void ()> cueFunction) {
	//0 duration tween with cue function as tween operation function. Sequence update logic ensures that this gets called once and does not take any sequence time
	tweenQueue.push_back(new CDBTweener::CTween(&CDBTweener::TWEQ_LINEAR, CDBTweener::TWEA_IN, 0, 0, std::bind(cueFunction), 0));
}

void Sequence::update(float deltaTime) {
	while (deltaTime > 0) {
		if (tweenQueue.empty()) return;

		CDBTweener::CTween& curTween = *(tweenQueue.front());
		curTween.step(deltaTime);

		//if we're still in the middle of a tween then there's nothing more to be done
		if (!curTween.isFinished()) return;

		//if curTween _is_ finished
		deltaTime -= (curTween.getElapsedSec() - curTween.getDurationSec());
 		delete tweenQueue.front();
		tweenQueue.pop_front();
	}
}

bool Sequence::isEmpty() {
	return tweenQueue.empty();
}
