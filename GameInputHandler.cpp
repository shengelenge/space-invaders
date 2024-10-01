#include "GameInputHandler.h"
#include "SoundEngine.h"
#include "GameScreen.h"

class BulletSpawner;

void GameInputHandler::initialize() {
	m_PlayerUpdateComponent = std::static_pointer_cast<PlayerUpdateComponent>(
		getPtrToScreenManagerRemoteControl()
		->shareGameObjectSharer()
		.findFirstObjectWithTag("Player")
		.getComponentByTypeAndSpecificType("update", "player"));
	m_PlayerTransformComponent = getPtrToScreenManagerRemoteControl()
		->shareGameObjectSharer()
		.findFirstObjectWithTag("Player")
		.getTransformComponent();
}

void GameInputHandler::handleGamepad() {
	float deadZone = 10.f;
	float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
	if (x < deadZone && x > -deadZone) {
		x = 0;
	}
	
	if (y < deadZone && y > -deadZone) {
		y = 0;
	}

	m_PlayerUpdateComponent->updateShipTravelWithController(x, y);

	// Has the player pressed the B button?
	if (sf::Joystick::isButtonPressed(0, 1)) {
		m_ButtonPressed = true;
	}

	// Has the player just released the B button?
	if (!sf::Joystick::isButtonPressed(0, 1) && m_ButtonPressed) {
		m_ButtonPressed = false;

		// Shoot a bullet
		SoundEngine::playShoot();
		sf::Vector2f spawnLocation;
		spawnLocation.x = m_PlayerTransformComponent->getLocation().x + m_PlayerTransformComponent->getSize().x / 2;
		spawnLocation.y = m_PlayerTransformComponent->getLocation().y;

		static_cast<GameScreen*>(getmParentScreen())->getBulletSpawner()->spawnBullet(spawnLocation, true);
	}
}

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
