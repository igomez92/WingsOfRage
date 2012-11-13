#include "GameStateManager.h"
#include "Character.h"

// Constructs a Game Manager object that runs the game
GameStateManager::GameStateManager()
	:tileHeight(64), tileWidth(64), windowHeight(1280), windowWidth(960)
{}

// Destroys any dynamically-allocated pointers that we create during the game.
GameStateManager::~GameStateManager()
{

}