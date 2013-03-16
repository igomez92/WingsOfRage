#pragma once

#include <list>
#include <queue>
#include "Enemy.h"

enum EnemyClass{
	ENEMY,
	TANKENEMY,
	MTANKENEMY,
	SLIDERENEMY
};

struct SpawnEntry {
	float spawnTime;
	EnemyClass enemyType;
	float xPos, yPos;
};

namespace LevelLoader {
	std::queue<SpawnEntry> loadLevel(std::string filename);
	void spawnEnemy(std::list<Enemy*>& enemyList, SpawnEntry& spawnEntry);
}
