#include "ScaleComponent.h"

ScaleComponent::ScaleComponent(GLfloat t_scale) : m_scale(t_scale)
{
}

ScaleComponent::~ScaleComponent()
{
}

void ScaleComponent::setScale(GLfloat t_scale)
{
	m_scale = t_scale;
}

GLfloat ScaleComponent::getScale() const
{
	return m_scale;
}
