#include "SelectUIPanel.h"
#include <iostream>

SelectUIPanel::SelectUIPanel(sf::Vector2i res) :
	// Create a new UIPanel
	// by calling  the super-class constructor
	UIPanel::UIPanel(res,
		(res.x / 10) * 2, // Start 2/10 across
		res.y / 6, // 1/6 of the resolution from the top
		(res.x / 10) * 6, // as wide as 6/10 of the resolution
		res.y / 2, // and as tall as 1/3 of the resolution
		0, 255, 255, 255) { // a, r, g, b
	m_ButtonWidth = res.x / 8.0;
	m_ButtonHeight = res.x / 20.0;
	m_ButtonPadding = res.x / 100.0;

	m_Text.setFillColor(sf::Color(255, 227, 21, 255));
	m_Text.setString("SPACE INVADERS");
	m_Text.Bold;

	m_Font.loadFromFile("fonts/space_invaders.ttf");
	m_Text.setFont(m_Font);

	m_Text.setPosition(sf::Vector2f(m_ButtonPadding, m_ButtonHeight));

	m_Text.setCharacterSize(115);

	initializeButtons();
}

void SelectUIPanel::initializeButtons() {
	// Buttons are positioned relative to the top left
	// corner of the UI panel (m_View in UIPanel)
	addButton(m_Text.getGlobalBounds().width / 2 - m_Text.getCharacterSize(),
		m_Text.getCharacterSize() * 3,
		m_ButtonWidth,
		m_ButtonHeight,
		0, 0, 0, 0,
		"Play");

	addButton(m_Text.getGlobalBounds().width / 2 - m_Text.getCharacterSize(),
		m_Text.getCharacterSize() * 4,
		m_ButtonWidth,
		m_ButtonHeight,
		0, 0, 0, 0,
		"Quit");

	//addButton(m_ButtonWidth + (m_ButtonPadding * 4),
	//	m_ButtonPadding,
	//	m_ButtonWidth,
	//	m_ButtonHeight,
	//	0, 0, 0, 255,
	//	"Quit");
}

void SelectUIPanel::draw(sf::RenderWindow& window) {
	show();
	UIPanel::draw(window);
	window.draw(m_Text);
}
