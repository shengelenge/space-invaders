#include "GameOverUIPanel.h"
#include "GameScreen.h"

bool GameScreen::m_GameOver;

GameOverUIPanel::GameOverUIPanel(sf::Vector2i res) :
	UIPanel(res,
		(res.x / 10) * 3,
		res.y / 4, // 20% resolution from the top
		(res.x / 10) * 4, // as wide as 1/3 of the resolution
		res.y / 3, // and as tall as 1/6 of the resolution
		0, 255, 255, 255) { // a, r, g, b
	m_ButtonWidth = res.x / 12.0;
	m_ButtonHeight = res.y / 15.0;
	m_ButtonPadding = res.x / 100.0;

	m_Text.setFillColor(sf::Color(254, 30, 30, 255)); // Blooody red
	m_Text.setString("GAME OVER");
	m_Text.Bold;

	m_Font.loadFromFile("fonts/space_invaders.ttf");
	m_Text.setFont(m_Font);

	m_Text.setPosition(sf::Vector2f(m_ButtonPadding, 0));
	m_Text.setCharacterSize(115);

	initializeButtons();
}

void GameOverUIPanel::initializeButtons() {
	addButton(m_ButtonWidth * 2 - m_ButtonPadding,
		m_ButtonHeight * 3,
		m_ButtonWidth,
		m_ButtonHeight,
		0, 0, 0, 0,
		"Play");

	addButton(m_ButtonWidth * 2 - m_ButtonPadding,
		m_ButtonHeight * 4,
		m_ButtonWidth,
		m_ButtonHeight,
		0, 0, 0, 0,
		"Home");

	//addButton(m_ButtonPadding,
	//	m_ButtonPadding,
	//	m_ButtonWidth,
	//	m_ButtonHeight,
	//	0, 255, 0, 255,
	//	"Play");

	//addButton(m_ButtonWidth + (m_ButtonPadding * 2),
	//	m_ButtonPadding,
	//	m_ButtonWidth,
	//	m_ButtonHeight,
	//	255, 0, 0, 255,
	//	"Home");
}

void GameOverUIPanel::draw(sf::RenderWindow& window) {
	if (GameScreen::m_GameOver) {
		show();
		UIPanel::draw(window);
		window.draw(m_Text);
	} else {
		hide();
	}
}

