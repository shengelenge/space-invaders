#include "UIPanel.h"

UIPanel::UIPanel(sf::Vector2i res, int x, int y, float width, float height, int alpha, int red, int green, int blue) {
	m_UIPanel.setFillColor(sf::Color(red, green, blue, alpha));

	// How big in pixels is the UI panel
	m_UIPanel.setSize(sf::Vector2f(width, height));

	// How big in pixels it the view
	m_View.setSize(width, height);

	// Where in pixels does the center of the view focus
	// This is most relevant when drawing a portion
	// of the game world
	// width / 2, height / 2 ensures it's exactly centered around the
	// RectangleShape, m_UIPanel
	m_View.setCenter(width / 2, height / 2);

	// Where in the window is the view positioned?
	float viewportStartX = 1.f / (res.x / x);
	float viewportStartY = 1.f / (res.y / y);
	float viewportSizeX = 1.f / (res.x / width);
	float viewportSizeY = 1.f / (res.y / height);

	// Params from left to right
	// StartX as a fraction of 1, startY as a fraction of 1
	// SizeX as a fraction of 1, sizeY as a fraction of 1
	m_View.setViewport(sf::FloatRect(viewportStartX, viewportStartY, viewportSizeX, viewportSizeY));
}

std::vector<std::shared_ptr<Button>> UIPanel::getButtons() {
	return m_Buttons;
}

void UIPanel::addButton(float x, float y,
	int width, int height,
	int red, int green, int blue, int alpha,
	std::string label) {
	m_Buttons.push_back(std::make_shared<Button>(sf::Vector2f(x, y),
		width, height,
		red, green, blue, alpha,
		label));
}

void UIPanel::draw(sf::RenderWindow& window) {
	window.setView(m_View);
	if (!m_Hidden) {
		window.draw(m_UIPanel);
		for (auto it = m_Buttons.begin(); it != m_Buttons.end(); it++) {
			(*it)->draw(window);
		}
	}
}

void UIPanel::show() { m_Hidden = false; }

void UIPanel::hide() { m_Hidden = true; }
