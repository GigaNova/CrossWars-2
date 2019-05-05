#include "VelocityComponent.h"

VelocityComponent::VelocityComponent(glm::vec3 t_velocity, glm::vec3 t_acceleration) : m_velocity(t_velocity), m_acceleration(t_acceleration)
{
}

VelocityComponent::~VelocityComponent()
{
}

void VelocityComponent::setVelocity(glm::vec3 t_velocity)
{
	m_velocity = t_velocity;
}

void VelocityComponent::setAcceleration(glm::vec3 t_acceleration)
{
	m_acceleration = t_acceleration;
}

glm::vec3 VelocityComponent::getVelocity() const
{
	return m_velocity;
}

glm::vec3 VelocityComponent::getAcceleration() const
{
	return m_acceleration;
}
