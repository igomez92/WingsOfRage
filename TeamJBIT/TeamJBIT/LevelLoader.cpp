#include "LevelLoader.h"
#include <fstream>
#include <cstring>

#include "SliderEnemy.h"
#include "TankEnemy.h"
#include "MTankEnemy.h"

//two helper functions first
EnemyClass parseEnemyType(char* typeString) {
	if (strcmp(typeString, "Enemy") == 0)
		return EnemyClass::ENEMY;
	if (strcmp(typeString, "SliderEnemy") == 0)
		return EnemyClass::SLIDERENEMY;
	if (strcmp(typeString, "TankEnemy") == 0)
		return EnemyClass::TANKENEMY;
	if (strcmp(typeString, "MTankEnemy") == 0)
		return EnemyClass::MTANKENEMY;
	
	//fallback to stock enemy :/
	return EnemyClass::ENEMY;
}

void stripWhitespace(char* string, int length) {
	char* newString = new char[length];

	int newStringIndex = 0;
	for (int i = 0; i < length; i++) {
		if (string[i] == 0) break;
		if (string[i] == ' ' || string[i] == '\t') continue;

		newString[newStringIndex++] = string[i]; //yes that's a deliberate postfix
	}

	newString[newStringIndex] = 0; //null terminate

	string = strcpy(string, newString);
	delete[] newString;
}

std::queue<SpawnEntry> LevelLoader::loadLevel(std::string filename) {
	std::queue<SpawnEntry> spawnQueue;
	std::ifstream levelFile (filename.c_str());

	char line[512]; //with current file format this is way, way more than enough space
	while (!levelFile.eof()) {
		levelFile.getline(line, 512);
		//strip whitespace		
		stripWhitespace(line, 512);

		//is this line a comment?
		if (line[0] == '/' && line[1] == '/') continue;
		//is this line empty?
		if (line[0] == 0) continue;

		SpawnEntry entry;
		entry.spawnTime = atof(strtok(line, ","	));
		entry.enemyType = parseEnemyType(strtok(NULL, ","));
		entry.xPos = atof(strtok(NULL, ","));
		entry.yPos = atof(strtok(NULL, ","));

		spawnQueue.push(entry);
	}

	levelFile.close();

	return spawnQueue;
}

void LevelLoader::spawnEnemy(std::list<Enemy*>& enemyList, SpawnEntry& entry) {
	switch (entry.enemyType) {
		case EnemyClass::ENEMY:
			enemyList.push_back(new Enemy("media/ball.png", sf::Vector2f(entry.xPos, entry.yPos)));
			break;
		case EnemyClass::SLIDERENEMY:
			enemyList.push_back(new SliderEnemy("media/ball.png", sf::Vector2f(entry.xPos, entry.yPos)));
			break;
		case EnemyClass::TANKENEMY:
			enemyList.push_back(new TankEnemy("media/ball.png", sf::Vector2f(entry.xPos, entry.yPos)));
			break;
		case EnemyClass::MTANKENEMY:
			enemyList.push_back(new MTankEnemy("media/ball.png", sf::Vector2f(entry.xPos, entry.yPos)));
			break;
	}
}
