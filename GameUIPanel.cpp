#include "GameUIPanel.h"
#include "WorldState.h"
#include <sstream>

int WorldState::SCORE;
int WorldState::LIVES;

GameUIPanel::GameUIPanel(sf::Vector2i res) :
	UIPanel(res,
		1, // The left
		1, // The top 
		res.x / 2, // 1/2 width screen
		res.y / 12,
		0, 255, 255, 255) { // a, r, g, b
	m_Text.setFillColor(sf::Color(152, 154, 254, 255));
	m_Text.setString("Score: 0 Lives: 3 Wave: 1");
	m_Font.loadFromFile("fonts/space_invaders.ttf");
	m_Text.setFont(m_Font);
	m_Text.setPosition(sf::Vector2f(15, 15));
	m_Text.setCharacterSize(50);
}

void GameUIPanel::draw(sf::RenderWindow& window) {
	UIPanel::draw(window);

	std::stringstream ss;
	ss << "Score: " << WorldState::SCORE << "   Lives: " << WorldState::LIVES << "   Wave: " << WorldState::WAVE_NUMBER;
	m_Text.setString(ss.str());

	window.draw(m_Text);
}
