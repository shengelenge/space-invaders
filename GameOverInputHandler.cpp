#include "GameOverInputHandler.h"
#include "SoundEngine.h"
#include "WorldState.h"
#include <iostream>

void GameOverInputHandler::handleKeyPressed(sf::Event& event, sf::RenderWindow& window) {
	if (event.key.code == sf::Keyboard::Escape) {
		SoundEngine::playClick();
		getPtrToScreenManagerRemoteControl()->SwitchScreens("Select");
	}
}

void GameOverInputHandler::handleLeftClick(std::string& buttonInteractedWith, sf::RenderWindow& window) {
	if (buttonInteractedWith == "Play") {
		SoundEngine::playClick();
		WorldState::WAVE_NUMBER = 0;
		getPtrToScreenManagerRemoteControl()->loadLevelInPlayMode("level1");
	} else if (buttonInteractedWith == "Home") {
		SoundEngine::playClick();
		getPtrToScreenManagerRemoteControl()->SwitchScreens("Select");
	}
}
