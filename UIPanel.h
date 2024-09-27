#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"

class UIPanel {
private:
	sf::ConvexShape m_UIPanel2;
	sf::RectangleShape m_UIPanel;
	bool m_Hidden = false;
	std::vector<std::shared_ptr<Button>> m_Buttons;

protected:
	float m_ButtonWidth = 0;
	float m_ButtonHeight = 0;
	float m_ButtonPadding = 0;

	sf::Font m_Font;
	sf::Text m_Text;

	void addButton(float x, float y, int width, int height,
		int red, int green, int blue, int alpha,
		std::string label);

public:
	sf::View m_View;

	UIPanel(sf::Vector2i res, int x, int y,
		float width, float height,
		int alpha, int red, int green, int blue);

	std::vector<std::shared_ptr<Button>> getButtons();
	virtual void draw(sf::RenderWindow& window);
	void show();
	void hide();
};


