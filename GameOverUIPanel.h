#pragma once
#include "UIPanel.h"

class GameOverUIPanel : public UIPanel {
private:
	void initializeButtons();

public:
	GameOverUIPanel(sf::Vector2i res);
	void virtual draw(sf::RenderWindow& window);
};


