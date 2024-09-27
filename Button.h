#pragma once
#include <SFML/Graphics.hpp>

class Button {
private:
	sf::RectangleShape m_Button;
	sf::Text m_ButtonText;
	sf::Font m_Font;

public:
	std::string m_Text;
	sf::FloatRect m_Collider;

	Button(sf::Vector2f position,
		float width, float height,
		int red, int green, int blue, int alpha,
		std::string text);

	void draw(sf::RenderWindow& window);
};


