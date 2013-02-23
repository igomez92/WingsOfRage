#include "SceneManager.h"

	SceneManager::SceneManager(){};
	SceneManager::~SceneManager(){};

	void SceneManager::changeScene(std::string sceneName){
		auto iter = sceneMap.begin();
		iter = sceneMap.find(sceneName);

		if( iter != sceneMap.end() ) {
			currentScene = iter->second;
		}
	}
	void SceneManager::addScene(std::string sceneName, IScene* sceneToAdd)
	{
		sceneMap.insert(std::make_pair(sceneName, sceneToAdd));
	}

	IScene* SceneManager::getCurrentScene()
	{
		return currentScene;
	}