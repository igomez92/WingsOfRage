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