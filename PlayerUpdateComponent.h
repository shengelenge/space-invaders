#pragma once
#include "UpdateComponent.h"
#include "TransformComponent.h"
#include "GameObjectSharer.h"
#include "RectColliderComponent.h"
#include "GameObject.h"

class PlayerUpdateComponent : public UpdateComponent {
private:
	std::string m_SpecificType = "player";

	std::shared_ptr<TransformComponent> m_TransformComponent;
	std::shared_ptr<RectColliderComponent> m_RectColliderComponent;

	float m_Speed = 50.0f;
	float m_XExtent = 0;
	float m_YExtent = 0;

	bool m_IsHoldingLeft = false;
	bool m_IsHoldingRight = false;
	bool m_IsHoldingUp = false;
	bool m_IsHoldingDown = false;

public:
	void updateShipTravelWithController(float x, float y);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();

	/****************************************************
	*****************************************************
	From Component interface base class
	*****************************************************
	*****************************************************/

	std::string Component::getSpecificType() {
		return m_SpecificType;
	}

	void Component::start(GameObjectSharer* gos, GameObject* self) {
		m_TransformComponent = std::static_pointer_cast<TransformComponent>(self->getComponentByTypeAndSpecificType("transform", "transform"));
		m_RectColliderComponent = std::static_pointer_cast<RectColliderComponent>(self->getComponentByTypeAndSpecificType("collider", "rect"));
	}

	/****************************************************
	*****************************************************
	From UpdateComponent
	*****************************************************
	*****************************************************/

	void update(float fps) override;
};

