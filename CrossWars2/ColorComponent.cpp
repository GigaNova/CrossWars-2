#include "ColorComponent.h"

ColorComponent::ColorComponent(glm::vec3 t_color) : m_color(t_color)
{
}

void ColorComponent::setColor(glm::vec3 t_color)
{
	m_color = t_color;
}

glm::vec3 ColorComponent::getColor() const
{
	return m_color;
}

ColorComponent::~ColorComponent()
{
}
