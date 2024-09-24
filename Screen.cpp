#include "Screen.h"

void Screen::initialize() {}

void Screen::addPanel(std::unique_ptr<UIPanel> uip, ScreenManagerRemoteControl* smrc, std::shared_ptr<InputHandler> ih) {
	ih->initializeInputHandler(smrc, uip->getButtons(), &uip->m_View, this);

	// Use move() because otherwise
	// the vector has a COPY which is not allowed
	m_Panels.push_back(std::move(uip));
	m_InputHandlers.push_back(ih);
}

void Screen::handleInput(sf::RenderWindow& window) {
	sf::Event event;
	auto it = m_InputHandlers.begin();
	auto end = m_InputHandlers.end();
	while (window.pollEvent(event)) {
		for (it; it != end; ++it) {
			(*it)->handleInput(window, event);
		}
	}
}

void Screen::update(float fps) {}

void Screen::draw(sf::RenderWindow& window) {
	auto it = m_Panels.begin();
	auto end = m_Panels.end();
	for (it; it != end; ++it) {
		(*it)->draw(window);
	}
}
