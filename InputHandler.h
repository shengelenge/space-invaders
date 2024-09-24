#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"
#include "Screen.h"
#include "ScreenManagerRemoteControl.h"

class Screen;

class InputHandler {
private:
	Screen* m_ParentScreen;
	std::vector<std::shared_ptr<Button>> m_Buttons;
	sf::View* m_PtrToUIPanelView;
	ScreenManagerRemoteControl* m_ScreenManagerRemoteControl;

public:
	void initializeInputHandler(
		ScreenManagerRemoteControl* smrc,
		std::vector<std::shared_ptr<Button>>,
		sf::View* ptrToUIView,
		Screen* parentScreen
	);

	void handleInput(sf::RenderWindow& window, sf::Event& event);

	virtual void handleGamepad();
	virtual void handleKeyPressed(sf::Event& event,
		sf::RenderWindow& window);

	virtual void handleKeyReleased(sf::Event& event,
		sf::RenderWindow& window);

	virtual void handleLeftClick(std::string& buttonInteractedWith,
		sf::RenderWindow& window);

	sf::View* getPtrToUIView();

	ScreenManagerRemoteControl* getPtrToScreenManagerRemoteControl();

	Screen* getmParentScreen();
};


