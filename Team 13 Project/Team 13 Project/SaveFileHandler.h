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
	int currentAttack;
	int currentLevel;
	int currentExperience;
	Status* listOfStatuses;
};

SaveFile* loadSaveFileOne();
SaveFile* loadSaveFileTwo();
SaveFile* loadSaveFileThree();

SaveFile* readFile(std::string saveFileToRead);

void saveFileOne();
void saveFileTwo();
void saveFileThree();

void saveFiles(std::string saveFileToWrite);

#endif // SAVE_FILE_HANDLER_H