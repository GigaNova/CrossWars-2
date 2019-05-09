#include "StaticLight.h"

StaticLight::StaticLight(const glm::vec3 t_position, glm::vec3 t_color) : m_position(t_position), m_color(t_color)
{
}

StaticLight::~StaticLight()
{
}

glm::vec3 StaticLight::getPosition() const
{
	return m_position;
}

glm::vec3 StaticLight::getColor() const
{
	return m_color;
}
