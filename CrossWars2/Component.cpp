#include "Component.h"

Component::Component()
{
}

Component::~Component()
{
}

void Component::setOwner(BaseEntity* t_entity)
{
	m_owner = t_entity;
}

BaseEntity* Component::getOwner()
{
	return m_owner;
}
