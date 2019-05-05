#include "BaseEntity.h"

BaseEntity::BaseEntity() 
{
	
}

BaseEntity::~BaseEntity()
{
}

void BaseEntity::addComponent(std::shared_ptr<Component> t_component)
{
	m_components[typeid(*t_component)] = t_component;
}
