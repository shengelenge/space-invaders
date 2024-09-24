#include "GameInputHandler.h"
#include "SoundEngine.h"
#include "GameScreen.h"

void GameInputHandler::initialize() {}

void GameInputHandler::handleGamepad() {}

void GameInputHandler::handleKeyPressed(sf::Event& event, sf::RenderWindow& window) {
	// Handle key presses
	if (event.key.code == sf::Keyboard::Escape) {
		SoundEngine::playClick();
		getPtrToScreenManagerRemoteControl()->SwitchScreens("Select");
	}
}

void GameInputHandler::handleKeyReleased(sf::Event& event, sf::RenderWindow& window) {}
