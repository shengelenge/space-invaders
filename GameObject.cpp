#include "GameObject.h"
#include <iostream>
#include "DevelopState.h"
#include "UpdateComponent.h"
#include "RectColliderComponent.h"

void GameObject::update(float fps) {
	if (m_Active && m_HasUpdateComponent) {
		for (int i = m_FirstUpdateComponentLocation; i < m_FirstUpdateComponentLocation + m_NumberUpdateComponents; i++) {
			std::shared_ptr<UpdateComponent> tempUpdate = std::static_pointer_cast<UpdateComponent>(m_Components[i]);
			if (tempUpdate->enabled()) {
				tempUpdate->update(fps);
			}
		}
	}
}

void GameObject::draw(sf::RenderWindow& window) {
	if (m_Active && m_HasGraphicsComponent) {
		if (m_Components[m_GraphicsComponentLocation]->enabled()) {
			getGraphicsComponent()->draw(window, getTransformComponent());
		}
	}
}

std::shared_ptr<GraphicsComponent> GameObject::getGraphicsComponent() {
	return std::static_pointer_cast<GraphicsComponent>(m_Components[m_GraphicsComponentLocation]);
}

std::shared_ptr<TransformComponent> GameObject::getTransformComponent() {
	return std::static_pointer_cast<TransformComponent>(m_Components[m_TransformComponentLocation]);
}

void GameObject::addComponent(std::shared_ptr<Component> component) {
	m_Components.push_back(component);
	component->enableComponent();

	if (component->getType() == "update") {
		m_HasUpdateComponent = true;
		m_NumberUpdateComponents++;
		if (m_NumberUpdateComponents == 1) {
			m_FirstUpdateComponentLocation = m_Components.size() - 1;
		}
	} else if (component->getType() == "graphics") {
		// No iteration in the draw method required
		m_HasGraphicsComponent = true;
		m_GraphicsComponentLocation = m_Components.size() - 1;
	} else if (component->getType() == "transform") {
		// Remember where the transform component is
		m_TransformComponentLocation = m_Components.size() - 1;
	} else if (component->getType() == "collider" && component->getSpecificType() == "rect") {
		// Remember where the collider component(s) is
		m_HasCollider = true;
		m_NumberRectColliderComponents++;
		if (m_NumberRectColliderComponents == 1) {
			m_FirstRectColliderComponentLocation = m_Components.size() - 1;
		}
	} 
}

void GameObject::setActive() {
	m_Active = true;
}

void GameObject::setInactive() {
	m_Active = false;
}

bool GameObject::isActive() {
	return m_Active;
}

void GameObject::setTag(std::string tag) {
	m_Tag = "" + tag;
}

std::string GameObject::getTag() {
	return m_Tag;
}

void GameObject::start(GameObjectSharer* gos) {
	auto it = m_Components.begin();
	auto end = m_Components.end();
	for (it; it != end; it++) {
		(*it)->start(gos, this);
	}
}

// Slow - only use in init and start
std::shared_ptr<Component> GameObject::getComponentByTypeAndSpecificType(std::string type, std::string specificType) {
	auto it = m_Components.begin();
	auto end = m_Components.end();
	for (it; it != end; it++) {
		if ((*it)->getType() == type) {
			if ((*it)->getSpecificType() == specificType) {
				return *it;
			}
		}
	}
#ifdef debuggingErrors
	std::cout << "Gameobject.cpp::getComponentByTypeAndSpecificType-"
		<< "COMPONENT NOT FOUND ERROR!" << std::endl;
#endif
	return m_Components[0];
}

sf::FloatRect& GameObject::getEncompassingRectCollider() {
	if (m_HasCollider) {
		return std::static_pointer_cast<RectColliderComponent>(
			m_Components[m_FirstRectColliderComponentLocation])->getColliderRectF();
	}
}

std::string GameObject::getEncompassingRectColliderTag() {
	return std::static_pointer_cast<RectColliderComponent>(
		m_Components[m_FirstRectColliderComponentLocation])->getColliderTag();
}

std::shared_ptr<UpdateComponent> GameObject::getFirstUpdateComponent() {
	return std::static_pointer_cast<UpdateComponent>(m_Components[m_FirstUpdateComponentLocation]);
}

bool GameObject::hasCollider() {
	return m_HasCollider;
}

bool GameObject::hasUpdateComponent() {
	return m_HasUpdateComponent;
}
