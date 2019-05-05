#include "RotationComponent.h"

RotationComponent::RotationComponent(float t_x, float t_y, float t_z) : m_rotation(glm::vec3(t_x, t_y, t_z))
{
}

RotationComponent::RotationComponent(glm::vec3 t_rotation) : m_rotation(t_rotation)
{
}

RotationComponent::~RotationComponent()
{
}

void RotationComponent::increaseRotation(glm::vec3 t_increase)
{
	m_rotation += t_increase;
}

void RotationComponent::setRotation(glm::vec3 t_rotation)
{
	m_rotation = t_rotation;
}

glm::vec3 RotationComponent::getRotation() const
{
	return m_rotation;
}
