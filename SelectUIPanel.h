#pragma once
#include "UIPanel.h"

class SelectUIPanel : public UIPanel {
private:
	void initializeButtons();

public:
	SelectUIPanel(sf::Vector2i res);
	void virtual draw(sf::RenderWindow& window);
};


