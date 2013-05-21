#pragma once

#include <SFML/Audio.hpp>

class SoundManager
{
	public:
		SoundManager();
		~SoundManager();
		sf::SoundBuffer buffer;
		sf::Sound sound;
		sf::Music music;
		void setMusic(std::string file);
		void playMusic();
		void stopMusic();

};