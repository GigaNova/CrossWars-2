#include "PositionComponent.h"

PositionComponent::PositionComponent(float t_x, float t_y, float t_z) : m_position(glm::vec3(t_x, t_y, t_z))
{
}

PositionComponent::PositionComponent(glm::vec3 t_position) : m_position(t_position)
{
}

PositionComponent::~PositionComponent()
{
}

void PositionComponent::increasePosition(glm::vec3 t_increase)
{
	m_position += t_increase;
}

void PositionComponent::setPosition(glm::vec3 t_position)
{
	m_position = t_position;
}

glm::vec3 PositionComponent::getPosition() const
{
	return m_position;
}
