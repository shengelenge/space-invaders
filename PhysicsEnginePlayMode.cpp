#include "PhysicsEnginePlayMode.h"
#include <iostream>
#include "DevelopState.h"
#include "SoundEngine.h"
#include "WorldState.h"
#include "InvaderUpdateComponent.h"
#include "BulletUpdateComponent.h"

void PhysicsEnginePlayMode::detectInvaderCollisions(std::vector<GameObject>& objects, const std::vector<int>& bulletPositions) {
	sf::Vector2f offScreen(-1, -1);

	auto invaderIt = objects.begin();
	auto invaderEnd = objects.end();
	for (invaderIt; invaderIt != invaderEnd; ++invaderIt) {
		if ((*invaderIt).isActive() && (*invaderIt).getTag() == "invader") {
			auto bulletIt = objects.begin();
			// Jump to the first bullet
			std::advance(bulletIt, bulletPositions[0]);
			auto bulletEnd = objects.end();
			for (bulletIt; bulletIt != bulletEnd; ++bulletIt) {
				if ((*invaderIt).getEncompassingRectCollider().intersects((*bulletIt).getEncompassingRectCollider())
					&& (*bulletIt).getTag() == "bullet"
					&& std::static_pointer_cast<BulletUpdateComponent>((*bulletIt).getFirstUpdateComponent())->m_BelongsToPlayer) {
					SoundEngine::playInvaderExplode();

					(*invaderIt).getTransformComponent()->getLocation() = offScreen;
					(*bulletIt).getTransformComponent()->getLocation() = offScreen;

					WorldState::SCORE++;
					WorldState::NUM_INVADERS--;
					(*invaderIt).setInactive();
				}
			}
		}
	}
}

void PhysicsEnginePlayMode::detectPlayerCollisionsAndIvaderDirection(std::vector<GameObject>& objects, const std::vector<int>& bulletPositions) {
	sf::Vector2f offScreen(-1, -1);
	sf::FloatRect playerCollider = m_Player->getEncompassingRectCollider();
	std::shared_ptr<TransformComponent> playerTransform = m_Player->getTransformComponent();
	sf::Vector2f playerLocation = playerTransform->getLocation();

	auto it = objects.begin();
	auto end = objects.end();
	for (it; it != end; ++it) {
		if ((*it).isActive() &&
			(*it).hasCollider() &&
			(*it).getTag() != "Player") {
			// Get the reference to all the parts of
			// the current game object we might need
			sf::FloatRect currentCollider = (*it).getEncompassingRectCollider();

			// Detect collisions between objects
			// with the player
			if (currentCollider.intersects(playerCollider)) {
				if ((*it).getTag() == "bullet") {
					SoundEngine::playPlayerExplode();
					WorldState::LIVES--;
					(*it).getTransformComponent()->getLocation() = offScreen;
				}

				if ((*it).getTag() == "invader") {
					SoundEngine::playPlayerExplode();
					SoundEngine::playInvaderExplode();
					WorldState::LIVES--;
					(*it).getTransformComponent()->getLocation() = offScreen;

					WorldState::SCORE++;
					(*it).setInactive();
				}
			}

			std::shared_ptr<TransformComponent> currentTransform = (*it).getTransformComponent();
			sf::Vector2f currentLocation = currentTransform->getLocation();
			std::string currentTag = (*it).getTag();
			sf::Vector2f currentSize = currentTransform->getSize();

			// Handle the direction and descent
			// of the invaders
			if (currentTag == "invader") {
				// This is an invader
				if (!m_NeedToDropDownAndReverse &&
					!m_InvaderHitWallThisFrame) {
					// Currently no need to dropdown
					// and reverse from previous frame
					// or any hits this frame
					if (currentLocation.x > WorldState::WORLD_WIDTH - currentSize.x) {
						// The invader is passed its
						// furthest right position
						if (std::static_pointer_cast<InvaderUpdateComponent>((*it).getFirstUpdateComponent())->isMovingRight()) {
							// The invader is travelling
							// right so set a flag that
							// an invader has collided
							m_InvaderHitWallThisFrame = true;
						}
					} else if (currentLocation.x < 0) {
						// The invader is passed its
						// furthest left position
						if (!std::static_pointer_cast<InvaderUpdateComponent>((*it).getFirstUpdateComponent())->isMovingRight()) {
							// The invader is travelling
							// left so set a flag that
							// an invader has collided
							m_InvaderHitWallThisFrame = true;
						}
					}
				} else if (m_NeedToDropDownAndReverse &&
					!m_InvaderHitWallPreviousFrame) {
					// Drop down and reverse
					std::static_pointer_cast<InvaderUpdateComponent>((*it).getFirstUpdateComponent())->dropDownAndReverse();
				}
			}
		}
	}
}

void PhysicsEnginePlayMode::handleInvaderDirection() {
	if (m_InvaderHitWallThisFrame) {
		m_NeedToDropDownAndReverse = true;
		m_InvaderHitWallThisFrame = false;
	} else {
		m_NeedToDropDownAndReverse = false;
	}
}

void PhysicsEnginePlayMode::initialize(GameObjectSharer& gos) {
	m_PlayerUpdateComponent = std::static_pointer_cast<PlayerUpdateComponent>(
		gos.findFirstObjectWithTag("Player").getComponentByTypeAndSpecificType("update", "player"));
}

void PhysicsEnginePlayMode::detectCollisions(std::vector<GameObject>& objects, const std::vector<int>& bulletPositions) {
	detectInvaderCollisions(objects, bulletPositions);
	detectPlayerCollisionsAndIvaderDirection(objects, bulletPositions);
	handleInvaderDirection();
}
