#include "PlayerUpdateComponent.h"
#include "WorldState.h"

void PlayerUpdateComponent::update(float fps) {
	if (sf::Joystick::isConnected(0)) {
		m_TransformComponent->getLocation().x += ((m_Speed / 100) * m_XExtent) * fps;
		m_TransformComponent->getLocation().y += ((m_Speed / 100) * m_YExtent) * fps;
	}

	// Left and right
	if (m_IsHoldingLeft) {
		m_TransformComponent->getLocation().x -= m_Speed * fps;
	} else if (m_IsHoldingRight) {
		m_TransformComponent->getLocation().x += m_Speed * fps;
	}

	// Up and down
	if (m_IsHoldingUp) {
		m_TransformComponent->getLocation().y -= m_Speed * fps;
	} else if (m_IsHoldingDown) {
		m_TransformComponent->getLocation().y += m_Speed * fps;
	}

	// Update the collider
	m_RectColliderComponent->setOrMoveCollider(
		m_TransformComponent->getLocation().x, 
		m_TransformComponent->getLocation().y, 
		m_TransformComponent->getSize().x, 
		m_TransformComponent->getSize().y);

	// Make sure the ship doesn't go outside the allowed area
	if (m_TransformComponent->getLocation().x > 
		WorldState::WORLD_WIDTH - m_TransformComponent->getSize().x) {
		m_TransformComponent->getLocation().x = 
			WorldState::WORLD_WIDTH - m_TransformComponent->getSize().x;
	} else if (m_TransformComponent->getLocation().x < 0) {
		m_TransformComponent->getLocation().x = 0;
	}

	if (m_TransformComponent->getLocation().y > 
		WorldState::WORLD_HEIGHT - m_TransformComponent->getSize().y) {
		m_TransformComponent->getLocation().y = 
			WorldState::WORLD_HEIGHT - m_TransformComponent->getSize().y;
	} else if (m_TransformComponent->getLocation().y < WorldState::WORLD_HEIGHT / 2) {
		m_TransformComponent->getLocation().y = WorldState::WORLD_HEIGHT / 2;
	}
}

void PlayerUpdateComponent::updateShipTravelWithController(float x, float y) {
	m_XExtent = x;
	m_YExtent = y;
}

void PlayerUpdateComponent::moveLeft() {
	m_IsHoldingLeft = true;
	stopRight();
}

void PlayerUpdateComponent::moveRight() {
	m_IsHoldingRight = true;
	stopLeft();
}

void PlayerUpdateComponent::moveUp() {
	m_IsHoldingUp = true;
	stopDown();
}

void PlayerUpdateComponent::moveDown() {
	m_IsHoldingDown = true;
	stopUp();
}

void PlayerUpdateComponent::stopLeft() {
	m_IsHoldingLeft = false;
}

void PlayerUpdateComponent::stopRight() {
	m_IsHoldingRight = false;
}

void PlayerUpdateComponent::stopUp() {
	m_IsHoldingUp = false;
}

void PlayerUpdateComponent::stopDown() {
	m_IsHoldingDown = false;
}
