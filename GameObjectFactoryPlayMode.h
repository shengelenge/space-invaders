#pragma once
#include <vector>
#include "GameObjectBlueprint.h"
#include "GameObject.h"

class GameObjectFactoryPlayMode {
public:
	void buildGameObject(GameObjectBlueprint& bp, std::vector<GameObject>& gameObjects);
};

