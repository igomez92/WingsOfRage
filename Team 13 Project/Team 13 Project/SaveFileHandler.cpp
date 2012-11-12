#include <fstream>
#include "SaveFileHandler.h"

SaveFile loadSaveFileOne(std::string saveOne)
{
	return readFile(saveOne);
}
SaveFile loadSaveFileTwo(std::string saveTwo)
{
	return readFile(saveTwo);
}
SaveFile loadSaveFileThree(std::string saveThree)
{
	return readFile(saveThree);
}
SaveFile readFile(std::string saveFileToRead)
{
	SaveFile file;

	return file;
}

void saveFileOne(std::string saveOne)
{
	saveFiles(saveOne);
}
void saveFileTwo(std::string saveTwo)
{
	saveFiles(saveTwo);
}
void saveFileThree(std::string saveThree)
{
	saveFiles(saveThree);
}
void saveFiles(std::string saveFileToWrite)
{

}