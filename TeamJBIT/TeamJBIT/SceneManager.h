#pragma once

#include <map>
#include "IScene.h"

class SceneManager {
public:
	static SceneManager& getInstance()
	{
		 static SceneManager instance;
		 return instance;
	}
	void changeScene(std::string sceneName);
	void addScene(std::string sceneName, IScene* sceneToAdd);
	IScene* getCurrentScene();

private:
	SceneManager();
	~SceneManager();
	std::map<std::string, IScene*> sceneMap;
	IScene* currentScene;
	SceneManager(SceneManager const&);
	void operator = (SceneManager const&);

};