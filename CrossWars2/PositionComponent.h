#pragma once
#include "Component.h"
#include <GLM/vec3.hpp>

class PositionComponent : public Component
{
public:
	PositionComponent(float t_x, float t_y, float t_z);
	PositionComponent(glm::vec3 t_position);
	~PositionComponent();

	void increasePosition(glm::vec3 t_increase);
	void setPosition(glm::vec3 t_position);

	glm::vec3 getPosition() const;
private:
	glm::vec3 m_position;
};

