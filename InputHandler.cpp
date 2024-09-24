#include <sstream>
#include "InputHandler.h"

void InputHandler::initializeInputHandler(
	ScreenManagerRemoteControl* smrc,
	std::vector<std::shared_ptr<Button>> buttons,
	sf::View* ptrToUIView,
	Screen* parentScreen) {
	m_ScreenManagerRemoteControl = smrc;
	m_Buttons = buttons;
	m_PtrToUIPanelView = ptrToUIView;
	m_ParentScreen = parentScreen;
}

void InputHandler::handleInput(sf::RenderWindow& window, sf::Event& event) {
	// Handle any key presses
	if (event.type == sf::Event::KeyPressed) {
		handleKeyPressed(event, window);
	}

	if (event.type == sf::Event::KeyReleased) {
		handleKeyReleased(event, window);
	}

	// Handle any left mouse click released
	if (event.type == sf::Event::MouseButtonReleased) {
		auto end = m_Buttons.end();

		for (auto i = m_Buttons.begin(); i != end; ++i) {
			if ((*i)->m_Collider.contains(
				window.mapPixelToCoords(sf::Mouse::getPosition(),
					(*getPtrToUIView())))) {
				// Capture the text of the button that was interacted
				// with and pass it to the specialised version
				// of this class if implemented
				handleLeftClick((*i)->m_Text, window);
				break;
			}
		}
	}

	handleGamepad();
}

void InputHandler::handleGamepad() {} // Do nothing unless handled by a derived class

void InputHandler::handleKeyPressed(sf::Event& event, sf::RenderWindow& window) {} // Do nothing unless handled by a derived class

void InputHandler::handleKeyReleased(sf::Event& event, sf::RenderWindow& window) {} // Do nothing unless handled by a derived class

void InputHandler::handleLeftClick(std::string& buttonInteractedWith, sf::RenderWindow& window) {} // Do nothing unless handled by a derived class

sf::View* InputHandler::getPtrToUIView() {
	return m_PtrToUIPanelView;
}

ScreenManagerRemoteControl* InputHandler::getPtrToScreenManagerRemoteControl() {
	return m_ScreenManagerRemoteControl;
}

Screen* InputHandler::getmParentScreen() {
	return m_ParentScreen;
}

