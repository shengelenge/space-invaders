#pragma once
#include "UpdateComponent.h"
#include "TransformComponent.h"
#include "GameObjectSharer.h"
#include "RectColliderComponent.h"
#include "GameObject.h"

class BulletUpdateComponent : public UpdateComponent {
private:
	std::string m_SpecificType = "bullet";
	std::shared_ptr<TransformComponent> m_TransformComponent;
	std::shared_ptr<RectColliderComponent> m_RectColliderComponent;

	float m_Speed = 0.75f;

	int m_AlienBulletSpeedModifier;
	int m_ModifierRandomComponent = 5;
	int m_MinimumAdditionalComponent = 5;

	bool m_MovingUp = true;

public:
	bool m_BelongsToPlayer = false;
	bool m_IsSpawned = false;

	void spawnForPlayer(sf::Vector2f spawnPosition);
	void spawnForInvader(sf::Vector2f spawnPosition);
	void deSpawn();
	bool isMovingUp();

	/****************************************************
	*****************************************************
	From Component interface base class
	*****************************************************
	*****************************************************/

	std::string Component::getSpecificType() {
		return m_SpecificType;
	}

	void Component::start(GameObjectSharer* gos, GameObject* self) {
		// Where is the specific invader
		m_TransformComponent = std::static_pointer_cast<TransformComponent>(self->getCompnentByTypeAndSpecificType("transform", "transform"));
		m_RectColliderComponent = std::static_pointer_cast<RectColliderComponent>(self->getCompnentByTypeAndSpecificType("collider", "rect"));
	}

	/****************************************************
	*****************************************************
	From UpdateComponent
	*****************************************************
	*****************************************************/

	void UpdateComponent::update(float fps) override;
};

