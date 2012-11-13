#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

class GameStateManager
{
public:
	// Constructs an object to run the game
	GameStateManager();
	// In case we have any dynamically-allocated pointers
	~GameStateManager();

private:
	int windowHeight;
	int windowWidth;
	int tileHeight;
	int tileWidth;
	// Add functions down here to run the game
};

#endif // GAME_STATE_MANAGER_H