#pragma once
#include "Model.h"
#include <GLM/vec3.hpp>

class BaseEntity
{
public:
	BaseEntity(Model* t_model, const glm::vec3& t_position, const glm::vec3& t_rotation, GLfloat t_scale);
	~BaseEntity();

	Model* getModel();
	glm::vec3 getPosition();
	glm::vec3 getRotation();
	GLfloat getScale();

	void move(glm::vec3 t_amount);
	void rotate(glm::vec3 t_amount);
	void scale(GLfloat t_amount);
private:
	Model* m_model;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	GLfloat m_scale;
};

