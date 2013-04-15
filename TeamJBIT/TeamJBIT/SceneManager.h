#pragma once

#include <map>
#include "IScene.h"

class SceneManager 
{
	public:
		static SceneManager& getInstance() 
		{
			 static SceneManager instance;
			 return instance;
		}
		void changeScene(std::string sceneName, bool deleteCurrentScene = false);
		void addScene(std::string sceneName, IScene* sceneToAdd);
		void deleteScene(std::string sceneName);
		IScene* getCurrentScene();

	private:
		SceneManager() {};
		~SceneManager() {};
		SceneManager(SceneManager const&);
		SceneManager& operator =(SceneManager const&);

		std::map<std::string, IScene*> sceneMap;
		IScene* currentScene;
};
