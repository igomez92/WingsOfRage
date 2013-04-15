#include "SceneManager.h"

void SceneManager::changeScene(std::string sceneName, bool deleteCurrentScene)
{
	auto iter = sceneMap.begin();
	iter = sceneMap.find(sceneName);

	if( iter != sceneMap.end() ) {
		if (currentScene)
			currentScene->leave();

		if (deleteCurrentScene)
			delete currentScene;

		currentScene = iter->second;
		currentScene->enter();
	}
}

void SceneManager::addScene(std::string sceneName, IScene* sceneToAdd)
{
	sceneMap.insert(std::make_pair(sceneName, sceneToAdd));
}

void SceneManager::deleteScene(std::string sceneName)
{
	auto iter = sceneMap.begin();
	iter = sceneMap.find(sceneName);

	if( iter != sceneMap.end() ) {
		delete iter->second;

		//you really shouldn't be deleting the current scene but this will save you from a crash if you do (assuming the current scene isn't the only scene left in the list)
		if (currentScene == iter->second) {
			currentScene = sceneMap.begin()->second;
		}			
	}
}

IScene* SceneManager::getCurrentScene()
{
	return currentScene;
}
