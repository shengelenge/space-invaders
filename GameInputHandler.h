#pragma once
#include "InputHandler.h"
#include "PlayerUpdateComponent.h"
#include "TransformComponent.h"

class GameScreen;

class GameInputHandler : public InputHandler {
private:
	std::shared_ptr<PlayerUpdateComponent> m_PlayerUpdateComponent;
	std::shared_ptr<TransformComponent> m_PlayerTransformComponent;

	bool m_ButtonPressed = false;

public:
	void initialize();
	void handleGamepad() override;
	void handleKeyPressed(sf::Event& event, sf::RenderWindow& window) override;
	void handleKeyReleased(sf::Event& event, sf::RenderWindow& window) override;
};

