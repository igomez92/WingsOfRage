#include "SoundManager.h"

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{

}

void SoundManager::setMusic(std::string file)
{
	music.openFromFile(file);
}

void SoundManager::playMusic()
{
	music.play();
	music.setLoop(true);
	music.setVolume(100);
}

void SoundManager::stopMusic()
{
	music.stop();
}