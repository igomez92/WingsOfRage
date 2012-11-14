#include <fstream>
#include <string>
#include "SaveFileHandler.h"

// Loads the first save file
SaveFile* loadSaveFileOne()
{
	return readFile("SaveFileOne.Save");
}
// Loads the second save file
SaveFile* loadSaveFileTwo()
{
	return readFile("SaveFileTwo.Save");
}
// Loadse the third save file
SaveFile* loadSaveFileThree()
{
	return readFile("SaveFileThree.Save");
}
// Reads the file that is passed to it, returning a save file
SaveFile* readFile(std::string saveFileToRead)
{
	SaveFile* file;// = new SaveFile;
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

	readFile.close();
	// Be sure to delete the pointer after finishing with the save file struct
	return file;
}

//Saves to the first save file
void saveFileOne(int playerX, int playerY, int currentHealth, int maxHealth, int currentAttack, 
				 int currentLevel, int currentExperience, Status* listOfStatuses)
{
	saveFiles("SaveFileOne.Save", playerX, playerY, currentHealth, maxHealth, 
		currentAttack, currentLevel, currentExperience, listOfStatuses);
}
// Saves to the second save file
void saveFileTwo(int playerX, int playerY, int currentHealth, int maxHealth, int currentAttack, 
				 int currentLevel, int currentExperience, Status* listOfStatuses)
{
	saveFiles("SaveFileTwo.Save", playerX, playerY, currentHealth, maxHealth, 
		currentAttack, currentLevel, currentExperience, listOfStatuses);
}
// Saves to the third save file.
void saveFileThree(int playerX, int playerY, int currentHealth, int maxHealth, int currentAttack, 
				 int currentLevel, int currentExperience, Status* listOfStatuses)
{
	saveFiles("SaveFileThree.Save", playerX, playerY, currentHealth, maxHealth, 
		currentAttack, currentLevel, currentExperience, listOfStatuses);
}
// Saves to the file passed to it.
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