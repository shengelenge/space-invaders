#include "SelectInputHandler.h"
#include "SoundEngine.h"
#include "WorldState.h"
#include <iostream>

int WorldState::WAVE_NUMBER;

void SelectInputHandler::handleKeyPressed(sf::Event& event, sf::RenderWindow& window) {
	// Quit the game
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		window.close();
	}
}

void SelectInputHandler::handleLeftClick(std::string& buttonInteractedWith, sf::RenderWindow& window) {
	if (buttonInteractedWith == "Play") {
		SoundEngine::playClick();
		WorldState::WAVE_NUMBER = 0;
		getPtrToScreenManagerRemoteControl()->loadLevelInPlayMode("level1");
	}

	if (buttonInteractedWith == "Quit") {
		SoundEngine::playClick();
		window.close();
	}
}
