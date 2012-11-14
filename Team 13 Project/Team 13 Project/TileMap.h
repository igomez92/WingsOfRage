//Written by Geoffrey Tucker

#include <vector>

#ifndef _TILE_MAP_H_
#define _TILE_MAP_H_

enum TileType
{
	EMPTY,
	GRASS,
	MUD,
	WATER,
	SAND,
	DIRT,
	STONE_WALL,
	ROCK
};

struct Tile
{
	TileType type;
	int x;
	int y;
	int id;
	int reference;

	Tile(int in_type, int in_x, int in_y, int in_id, int in_reference)
	{
		type = (TileType) in_type;
		x = in_x;
		y = in_y;
		id = in_id;
		reference = in_reference;
	}
};

class TileMap
{
public:
	//Constructor
	TileMap(int mapWidth, int mapHeight, std::vector< std::vector< Tile* >* >* map);

	//Destructor
	~TileMap();

	/*
	* Returns tile from the 2D array based
	* on the x and y parameters
	*/
	Tile* getTile(int x, int y);

	//Getters
	int getMapWidth() { return mapWidth; }
	int getMapHeight() { return mapHeight; }
private:
	//2D vector of Tile structs
	std::vector< std::vector< Tile* >* >* map;
	int mapWidth;
	int mapHeight;
};

#endif