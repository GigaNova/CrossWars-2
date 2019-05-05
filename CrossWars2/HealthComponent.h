#pragma once
#include "Component.h"
class HealthComponent : public Component
{
public:
	HealthComponent(float t_value);
	HealthComponent(float t_value, float t_max_value);
	~HealthComponent();

	void setHealth(float t_value);
	void IncreaseHealth(float t_value);

	float getValue() const;
private:
	float m_value;
	float m_max_value;
};

