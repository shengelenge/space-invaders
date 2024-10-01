#pragma once
#include "GameObjectSharer.h"
#include "PlayerUpdateComponent.h"

class PhysicsEnginePlayMode {
private:
	std::shared_ptr<PlayerUpdateComponent> m_PlayerUpdateComponent;

	GameObject* m_Player;
	bool m_InvaderHitWallThisFrame = false;
	bool m_InvaderHitWallPreviousFrame = false;
	bool m_NeedToDropDownAndReverse = false;
	bool m_CompletedDropDownAndReverse = false;

	void detectInvaderCollisions(std::vector<GameObject>& objects, const std::vector<int>& bulletPositions);
	void detectPlayerCollisionsAndIvaderDirection(std::vector<GameObject>& objects, const std::vector<int>& bulletPositions);
	void handleInvaderDirection();

public:
	void initialize(GameObjectSharer& gos);
	void detectCollisions(std::vector<GameObject>& objects, const std::vector<int>& bulletPositions);
};

