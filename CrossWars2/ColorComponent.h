#pragma once
#include "Component.h"
#include <GLM/vec3.hpp>

class ColorComponent : public Component
{
public:
	ColorComponent(glm::vec3 t_color);
	~ColorComponent();

	void setColor(glm::vec3 t_color);
	glm::vec3 getColor() const;
private:
	glm::vec3 m_color;
};

