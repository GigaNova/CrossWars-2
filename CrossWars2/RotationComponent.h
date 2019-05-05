#pragma once
#include "Component.h"
#include <GLM/vec3.hpp>

class RotationComponent : public Component
{
public:
	RotationComponent(float t_x, float t_y, float t_z);
	RotationComponent(glm::vec3 t_rotation);
	~RotationComponent();

	void increaseRotation(glm::vec3 t_increase);
	void setRotation(glm::vec3 t_rotation);

	glm::vec3 getRotation() const;
private:
	glm::vec3 m_rotation;
};

