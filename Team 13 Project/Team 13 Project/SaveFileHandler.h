#ifndef SAVE_FILE_HANDLER_H
#define SAVE_FILE_HANDLER_H

#include <string>
#include "Status.h"

struct SaveFile
{
	int playerX;
	int playerY;
	int currentHealth;
	int currentMaxHealth;
	int currentLevel;
	int currentExperience;
	Status* listOfStatuses;
};

SaveFile loadSaveFileOne(std::string saveOne);
SaveFile loadSaveFileTwo(std::string saveTwo);
SaveFile loadSaveFileThree(std::string saveThree);

SaveFile readFile(std::string saveFileToRead);

void saveFileOne(std::string saveOne);
void saveFileTwo(std::string saveTwo);
void saveFileThree(std::string saveThree);

void saveFiles(std::string saveFileToWrite);

#endif // SAVE_FILE_HANDLER_H