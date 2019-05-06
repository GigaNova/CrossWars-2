#include "ComponentManager.h"
#include <algorithm>


ComponentManager::ComponentManager()
{
}


ComponentManager::~ComponentManager()
{
}

void ComponentManager::registerComponent(Component* t_component)
{
	m_components.push_back(t_component);
}

void ComponentManager::removeComponent(Component* t_component)
{
	m_components.erase(std::remove(m_components.begin(), m_components.end(), t_component), m_components.end());
}

std::vector<Component*>* ComponentManager::getComponents()
{
	return &m_components;
}
