#pragma once
#include <vector>
#include <string>
#include "GameObject.h"
#include "BlueprintObjectParser.h"
#include "GameObjectFactoryPlayMode.h"

class PlayModeObjectLoader {
private:
	BlueprintObjectParser m_BlueprintObjectParser;
	GameObjectFactoryPlayMode m_GameObjectFactoryPlayMode;

public:
	void loadGameObjectForPlayMode(std::string pathToFile, std::vector<GameObject>& gameObjects);
};

