#pragma once
#include <GLM/vec3.hpp>

class StaticLight
{
public:
	StaticLight(glm::vec3 t_position, glm::vec3 t_color);
	~StaticLight();

	glm::vec3 getPosition() const;
	glm::vec3 getColor() const;
private:
	glm::vec3 m_position;
	glm::vec3 m_color;
};

