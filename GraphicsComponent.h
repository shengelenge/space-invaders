#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include "GameObjectSharer.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class GraphicsComponent : public Component {
private:
	std::string m_Type = "graphics";
	bool m_Enabled = false;

public:
	virtual void draw(sf::RenderWindow& window, std::shared_ptr<TransformComponent> t) = 0;

	virtual void initializeGraphics(std::string bitmapName, sf::Vector2f objectSize) = 0;

	/****************************************************
	*****************************************************
	From Component interface
	*****************************************************
	*****************************************************/

	std::string Component::getType() {
		return m_Type;
	}

	void Component::disableComponent() {
		m_Enabled = false;
	}

	void Component::enableComponent() {
		m_Enabled = true;
	}

	bool Component::enabled() {
		return m_Enabled;
	}

	void Component::start(GameObjectSharer* gos, GameObject* self) {
		// Do nothing
	}
};

