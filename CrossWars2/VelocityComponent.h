#pragma once
#include "Component.h"
#include <GLM/vec3.hpp>

class VelocityComponent : public Component
{
public:
	VelocityComponent(glm::vec3 t_velocity, glm::vec3 t_acceleration);
	~VelocityComponent();

	void setVelocity(glm::vec3 t_velocity);
	void setAcceleration(glm::vec3 t_acceleration);

	glm::vec3 getVelocity() const;
	glm::vec3 getAcceleration() const;
private:
	glm::vec3 m_velocity;
	glm::vec3 m_acceleration;
};

