#include "BaseEntity.h"
#include "ComponentManager.h"

BaseEntity::BaseEntity() 
{
	static int id = 0;
	++id;
	m_id = id;

	Logger::GetInstance()->logAction("Created entity #" + std::to_string(m_id));
}

BaseEntity::~BaseEntity()
{
}

void BaseEntity::addComponent(Component* t_component)
{
	m_components[typeid(*t_component)] = t_component;
	t_component->setOwner(this);
	ComponentManager::GetInstance()->registerComponent(t_component);
}

std::unordered_map<std::type_index, Component*>* BaseEntity::getComponents()
{
	return &m_components;
}
