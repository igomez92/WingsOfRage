//Written by Geoffrey Tucker

#include "TileMap.h"
#include "EngineException.h"

TileMap::TileMap(int mapWidth, int mapHeight, std::vector< std::vector< Tile* >* >* map)
{
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
	this->map = map;
}

TileMap::~TileMap()
{
	//iterate through and delete all of the tiles
	for (int x = 0; x < this->map->size(); x++)
	{
		for (int y = 0; y < this->map->at(x)->size(); y++)
		{
			delete this->map->at(x)->at(y);
		}
		delete this->map->at(x);
	}
	delete this->map;
}

Tile* TileMap::getTile(int x, int y)
{
	if(x >= mapWidth || y >= mapHeight || x < 0 || y < 0)
	{
		throw new EngineException("TileOutOfBoundsException");
		return reinterpret_cast<Tile*>(0);
	}
	return this->map->at(x)->at(y);
}