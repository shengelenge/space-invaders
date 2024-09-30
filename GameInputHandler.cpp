#include "GameInputHandler.h"
#include "SoundEngine.h"
#include "GameScreen.h"

class BulletSpawner;

void GameInputHandler::initialize() {}

void GameInputHandler::handleGamepad() {}

void GameInputHandler::handleKeyPressed(sf::Event& event, sf::RenderWindow& window) {
	// Handle key presses
	if (event.key.code == sf::Keyboard::Escape) {
		SoundEngine::playClick();
		getPtrToScreenManagerRemoteControl()->SwitchScreens("Select");
	}

	if (event.key.code == sf::Keyboard::Left) {
		m_PlayerUpdateComponent->moveLeft();
	}

	if (event.key.code == sf::Keyboard::Right) {
		m_PlayerUpdateComponent->moveRight();
	}

	if (event.key.code == sf::Keyboard::Up) {
		m_PlayerUpdateComponent->moveUp();
	}

	if (event.key.code == sf::Keyboard::Down) {
		m_PlayerUpdateComponent->moveDown();
	}
}

void GameInputHandler::handleKeyReleased(sf::Event& event, sf::RenderWindow& window) {
	if (event.key.code == sf::Keyboard::Left) {
		m_PlayerUpdateComponent->stopLeft();
	} else if (event.key.code == sf::Keyboard::Right) {
		m_PlayerUpdateComponent->stopRight();
	} else if (event.key.code == sf::Keyboard::Up) {
		m_PlayerUpdateComponent->stopUp();
	} else if (event.key.code == sf::Keyboard::Down) {
		m_PlayerUpdateComponent->stopDown();
	} else if (event.key.code == sf::Keyboard::Space) {
		// Shoot a bullet
		SoundEngine::playShoot();
		sf::Vector2f spawnLocation;
		
		spawnLocation.x = m_PlayerTransformComponent->getLocation().x + m_PlayerTransformComponent->getSize().x / 2;
		spawnLocation.y = m_PlayerTransformComponent->getLocation().y;

		static_cast<GameScreen*>(getmParentScreen())->spawnBullet(spawnLocation, true);
	}
}
