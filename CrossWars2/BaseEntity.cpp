#include "BaseEntity.h"

BaseEntity::BaseEntity(Model* t_model, const glm::vec3& t_position, const glm::vec3& t_rotation, GLfloat t_scale) 
: m_model(t_model), m_position(t_position), m_rotation(t_rotation), m_scale(t_scale)
{
	
}

BaseEntity::~BaseEntity()
{
}

Model* BaseEntity::getModel()
{
	return m_model;
}

glm::vec3 BaseEntity::getPosition()
{
	return m_position;
}

glm::vec3 BaseEntity::getRotation()
{
	return m_rotation;
}

GLfloat BaseEntity::getScale()
{
	return m_scale;
}

void BaseEntity::move(const glm::vec3 t_amount)
{
	m_position += t_amount;
}

void BaseEntity::rotate(const glm::vec3 t_amount)
{
	m_rotation += t_amount;
}

void BaseEntity::scale(GLfloat t_amount)
{
	m_scale += t_amount;
}
