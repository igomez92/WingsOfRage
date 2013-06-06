#include "LevelLoader.h"
#include <fstream>
#include <cstring>
#include <tuple>

#include "SliderEnemy.h"
#include "TankEnemy.h"
#include "MTankEnemy.h"
#include "CircleEnemy.h"
#include "MeleeEnemy.h"
#include "SpiralEnemy.h"

//two helper functions first
LevelLoader::EntitySpawnType parseEntityType(char* typeString) {

	//enemies
	if (strcmp(typeString, "Enemy") == 0)
		return LevelLoader::EntitySpawnType::ENEMY;
	if (strcmp(typeString, "SliderEnemy") == 0)
		return LevelLoader::EntitySpawnType::SLIDERENEMY;
	if (strcmp(typeString, "TankEnemy") == 0)
		return LevelLoader::EntitySpawnType::TANKENEMY;
	if (strcmp(typeString, "MTankEnemy") == 0)
		return LevelLoader::EntitySpawnType::MTANKENEMY;
	if (strcmp(typeString, "CircleEnemy") == 0)
		return LevelLoader::EntitySpawnType::CIRCLEENEMY;
	if (strcmp(typeString, "MeleeEnemy") == 0)
		return LevelLoader::EntitySpawnType::MELEEENEMY;
	if (strcmp(typeString, "SpiralEnemy") == 0)
		return LevelLoader::EntitySpawnType::SPIRALENEMY;

	//general entities
	if (strcmp(typeString, "TextBox") == 0)
		return LevelLoader::EntitySpawnType::TEXTBOX;

	//fallback entity :/
	return LevelLoader::EntitySpawnType::INVALID;
}

void stripWhitespace(char* string, int length) {
	char* newString = new char[length];

	int newStringIndex = 0;
	bool inQuotes = false;

	for (int i = 0; i < length; i++) {
		if (string[i] == 0) break;

		//handle quotes
		if (!inQuotes && string[i] == '"') 
			inQuotes = true;
		else if (inQuotes && string[i] == '"')
			inQuotes = false;
		
		if (!inQuotes)
			if (string[i] == ' ' || string[i] == '\t') continue;

		newString[newStringIndex++] = string[i]; //yes that's a deliberate postfix
	}

	newString[newStringIndex] = 0; //null terminate

	string = strcpy(string, newString);
	delete[] newString;
}

std::queue<LevelLoader::EntitySpawnEntry> LevelLoader::loadLevel(std::string filename) {
	std::queue<LevelLoader::EntitySpawnEntry> spawnQueue;
	std::ifstream levelFile (filename.c_str());

	char line[512]; //with current file format this is way, way more than enough space
	while (!levelFile.eof()) {
		levelFile.getline(line, 512);
		stripWhitespace(line, 512);

		//is this line a comment?
		if (line[0] == '/' && line[1] == '/') continue;
		//is this line empty?
		if (line[0] == 0) continue;

		LevelLoader::EntitySpawnEntry entry;
		entry.spawnTime = atof(strtok(line, ","	));
		entry.entityType = parseEntityType(strtok(NULL, ","));
		entry.xPos = atof(strtok(NULL, ","));
		entry.yPos = atof(strtok(NULL, ","));
		entry.data = nullptr;

		//some entities use extra data (e.g. textboxes store string and time to show on screen)
		switch(entry.entityType) {
			case EntitySpawnType::TEXTBOX:
				std::string captionText = strtok(NULL, "\"");
				float timeToShow = atof(strtok(NULL, "\","));
				std::tuple<std::string, float>* packed = new std::tuple<std::string, float>(captionText, timeToShow);		
				entry.data = packed;
				break;
		}

		spawnQueue.push(entry);
	}

	levelFile.close();

	return spawnQueue;
}
