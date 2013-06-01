#pragma once

#include <list>
#include <queue>

namespace LevelLoader {
	enum EntitySpawnType {
		INVALID,

		TEXTBOX,

		ENEMY,
		TANKENEMY,
		MTANKENEMY,
		SLIDERENEMY,
		CIRCLEENEMY,
		MELEEENEMY,
		SPIRALENEMY
	};

	struct EntitySpawnEntry {
		float spawnTime;
		EntitySpawnType entityType;
		float xPos, yPos;
		void* data;
	};

	std::queue<EntitySpawnEntry> loadLevel(std::string filename);
}
