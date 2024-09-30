#include "InvaderUpdateComponent.h"
#include "BulletSpawner.h"
#include "WorldState.h"
#include "SoundEngine.h"

void InvaderUpdateComponent::update(float fps) {
	if (m_MovingRight) {
		m_TransformComponent->getLocation().x += m_Speed * fps;
	} else {
		m_TransformComponent->getLocation().x -= m_Speed * fps;
	}

	// Update the collider
	m_RectColliderComponent->setOrMoveCollider(
		m_TransformComponent->getLocation().x,
		m_TransformComponent->getLocation().y,
		m_TransformComponent->getSize().x,
		m_TransformComponent->getSize().y);

	m_TimeSinceLastShot += fps;

	// Is the middle of the invader above
	// player +- 1 world units
	if (m_TransformComponent->getLocation().x + (m_TransformComponent->getSize().x / 2) >
		(m_PlayerTransformComponent->getLocation().x - m_AccuracyModifier) &&
		m_TransformComponent->getLocation().x + (m_TransformComponent->getSize().x / 2) <
		(m_PlayerTransformComponent->getLocation().x + m_AccuracyModifier)) {
		// Has the invader waited long enough since th last shot
		if (m_TimeBetweenShots > m_TimeSinceLastShot) {
			SoundEngine::playShoot();
			sf::Vector2f spawnLocation;
			spawnLocation.x = m_TransformComponent->getLocation().x + (m_TransformComponent->getSize().x / 2);
			spawnLocation.y = m_TransformComponent->getLocation().y + m_TransformComponent->getSize().y;

			m_BulletSpawner->spawnBullet(spawnLocation, false);
			srand(m_RandSeed);
			int mTimeBetweenShots = (((rand() % 10)) + 1) / WorldState::WAVE_NUMBER;

			m_TimeSinceLastShot = 0;
		}
	}
}

void InvaderUpdateComponent::dropDownAndReverse() {
	m_MovingRight = !m_MovingRight;
	m_TransformComponent->getLocation().y += m_TransformComponent->getSize().y;
	m_Speed += (WorldState::WAVE_NUMBER) + (WorldState::NUM_INVADERS_AT_START - WorldState::NUM_INVADERS) * m_SpeedModifier;
}

bool InvaderUpdateComponent::isMovingRight() {
	return m_MovingRight;
}

void InvaderUpdateComponent::initializeBulletSpawner(BulletSpawner* bulletSpawner, int randSeed) {
	m_BulletSpawner = bulletSpawner;
	m_RandSeed = randSeed;
	srand(m_RandSeed);
	m_TimeBetweenShots = (rand() % 15 + m_RandSeed);

	m_AccuracyModifier = (rand() % 2);
	m_AccuracyModifier += 0 + static_cast<float> (rand() / (static_cast<float> (RAND_MAX / (10))));
}

