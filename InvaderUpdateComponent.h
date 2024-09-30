#pragma once
#include "UpdateComponent.h"
#include "TransformComponent.h"
#include "GameObjectSharer.h"
#include "RectColliderComponent.h"
#include "GameObject.h"

class BulletSpawner;

class InvaderUpdateComponent : public UpdateComponent {
private:
	std::string m_SpecificType = "invader";

	std::shared_ptr<TransformComponent> m_TransformComponent;
	std::shared_ptr<RectColliderComponent> m_RectColliderComponent;
	std::shared_ptr<TransformComponent> m_PlayerTransformComponent;
	std::shared_ptr<RectColliderComponent> m_PlayerRectColliderComponent;

	BulletSpawner* m_BulletSpawner;

	float m_Speed = 10.0f;
	bool m_MovingRight = true;
	float m_TimeSinceLastShot;
	float m_TimeBetweenShots = 5.0f;
	float m_AccuracyModifier;
	float m_SpeedModifier = 0.05;
	int m_RandSeed;

public:
	void dropDownAndReverse();
	bool isMovingRight();
	void initializeBulletSpawner(BulletSpawner* bulletSpawner, int randSeed);

	/****************************************************
	*****************************************************
	From Component interface base class
	*****************************************************
	*****************************************************/

	std::string getSpecificType() {
		return m_SpecificType;
	}

	void Component::start(GameObjectSharer* gos, GameObject* self) {
		// Where is the player?
		m_PlayerTransformComponent = std::static_pointer_cast<TransformComponent>(
			gos->findFirstObjectWithTag("Player")
			.getComponentByTypeAndSpecificType("transform", "transform"));

		m_PlayerRectColliderComponent = std::static_pointer_cast<RectColliderComponent>(
			gos->findFirstObjectWithTag("Player")
			.getComponentByTypeAndSpecificType("collider", "rect"));

		// Where is the specific invader
		m_TransformComponent = std::static_pointer_cast<TransformComponent>(
			self->getComponentByTypeAndSpecificType("transform", "transform"));

		m_RectColliderComponent = std::static_pointer_cast<RectColliderComponent>(
			self->getComponentByTypeAndSpecificType("collider", "rect"));
	}

	/****************************************************
	*****************************************************
	From UpdateComponent
	*****************************************************
	*****************************************************/

	void update(float fps) override;
};

