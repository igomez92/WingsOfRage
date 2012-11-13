#include <fstream>
#include <string>
#include "SaveFileHandler.h"


SaveFile* loadSaveFileOne()
{
	return readFile("SaveFileOne.Save");
}
SaveFile* loadSaveFileTwo()
{
	return readFile("SaveFileTwo.Save");
}
SaveFile* loadSaveFileThree()
{
	return readFile("SaveFileThree.Save");
}
SaveFile* readFile(std::string saveFileToRead)
{
	SaveFile* file = new SaveFile;
	std::ifstream readFile (saveFileToRead);
	
	readFile >> file->playerX;
  	readFile >> file->playerY;
	readFile >> file->currentHealth;
	readFile >> file->currentMaxHealth;
	readFile >> file->currentAttack;
	readFile >> file->currentLevel;
	readFile >> file->currentExperience;
	
	for(int i = 0; i < 5; i++)
	{
		// Create Statuses here

	}

	// Be sure to delete the pointer after finishing with the save file struct
	return file;
}

void saveFileOne(int playerX, int playerY, int currentHealth, int maxHealth, int currentAttack, 
				 int currentLevel, int currentExperience, Status* listOfStatuses)
{
	saveFiles("SaveFileOne.Save");
}
void saveFileTwo()
{
	saveFiles("SaveFileTwo.Save");
}
void saveFileThree()
{
	saveFiles("SaveFileThree.Save");
}
void saveFiles(std::string saveFileToWrite, int playerX, int playerY, int currentHealth, 
			   int maxHealth, int currentAttack, int currentLevel, int currentExperience, 
			   Status* listOfStatuses)
{
	std::ofstream myfile;
	myfile.open (saveFileToWrite);
	myfile << playerX << std::endl;
	myfile << playerY << std::endl;
	myfile << currentHealth << std::endl;
	myfile << maxHealth << std::endl;
	myfile << currentAttack << std::endl;
	myfile << currentLevel << std::endl;

	/*for(int i = 0; i < 5; i++)
	{
		myfile << listOfStatuses[i].type;
	}*/

	myfile.close();
}