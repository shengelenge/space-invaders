#pragma once
#include "ColliderComponent.h"
#include <SFML/Graphics.hpp>

class RectColliderComponent :public ColliderComponent {
private:
	std::string m_SpecificType = "rect";
	sf::FloatRect m_Collider;
	std::string m_Tag = "";

public:
	RectColliderComponent(std::string name);
	std::string getColliderTag();
	void setOrMoveCollider(float x, float y, float width, float height);

	sf::FloatRect& getColliderRectF();

	/****************************************************
	*****************************************************
	From Component interface base class
	*****************************************************
	*****************************************************/

	std::string getSpecificType() {
		return m_SpecificType;
	}

	void Component::start(GameObjectSharer* gos, GameObject* self) {};
};

