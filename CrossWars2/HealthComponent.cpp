#include "HealthComponent.h"

HealthComponent::HealthComponent(float t_value) : m_value(t_value), m_max_value(t_value)
{
}

HealthComponent::HealthComponent(float t_value, float t_max_value) : m_value(t_value), m_max_value(t_max_value)
{
}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::setHealth(float t_value)
{
	m_value = t_value;
}

void HealthComponent::IncreaseHealth(float t_value)
{
	if(m_value + t_value > m_max_value)
	{
		m_value = m_max_value;
	}
	else if(m_value + t_value < 0)
	{
		m_value = 0;
	}
	else
	{
		m_value += t_value;
	}
}

float HealthComponent::getValue() const
{
	return m_value;
}
